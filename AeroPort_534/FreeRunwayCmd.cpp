#include "FreeRunwayCmd.h"
#include "AirportManager.h"
#include "Ticket.h"
#include <iostream>
#include <iomanip>

FreeRunwayCmd::FreeRunwayCmd(std::stringstream& ss) : runwayId(-1), calculatedTax(0.0), revenue(0.0) {
    std::string runwayStr;
    ss >> runwayStr;
    if (!runwayStr.empty() && runwayStr[0] == 'R') {
        try {
            runwayId = std::stoi(runwayStr.substr(1));
        }
        catch (...) {
            runwayId = -1;
        }
    }
}

void FreeRunwayCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || (currentUser->getRole() != Role::Dispatcher && currentUser->getRole() != Role::Admin)) {
        std::cout << "[Error] Unauthorized! Only Traffic Control can free runways.\n";
        return;
    }

    targetRunway = manager.findRunway(runwayId);
    if (!targetRunway) {
        std::cout << "[Error] Runway R" << runwayId << " not found!\n";
        return;
    }

    if (targetRunway->getStatus() != RunwayStatus::Occupied) {
        std::cout << "[Error] Runway R" << runwayId << " is not currently occupied!\n";
        return;
    }

    auto plane = targetRunway->getCurrentAircraft();
    if (!plane) {
        std::cout << "[Error] Runway R" << runwayId << " is occupied but has no aircraft assigned!\n";
        return;
    }

    for (const auto& flight : manager.getAllFlights()) {
        if (flight->getStatus() == FlightStatus::Boarding && flight->getAircraft() == plane) {
            targetFlight = flight;
            break;
        }
    }

    if (!targetFlight) {
        std::cout << "[Error] No active boarding flight found for the aircraft on runway R" << runwayId << "!\n";
        return;
    }

    revenue = 0.0;
    for (const auto& ticket : targetFlight->getTickets()) {
        revenue += ticket->getPaidAmount();
    }

    calculatedTax = plane->calculateAirportTax(revenue);
    double profit = revenue - calculatedTax;

    auto airline = manager.findAirlineByAircraft(plane->getId());

    if (airline) {
        airline->deductFunds(calculatedTax);
        airline->addFunds(revenue); 
    }

    int oldHealth = plane->getHealth();
    plane->processFlightEnd();
    int newHealth = plane->getHealth();

    targetRunway->releaseRunway();
    targetFlight->setStatus(FlightStatus::Departed);

    std::cout << "[System] Runway R" << runwayId << " freed. Flight " << targetFlight->getFlightId() << " status -> Departed.\n";
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "[Finance] Ticket Sales: " << revenue << " EUR. Airport Tax Deducted: " << calculatedTax << " EUR. Profit: " << profit << " EUR.\n";
    std::cout << "[Health] Aircraft ID: " << plane->getId() << " health decreased by " << (oldHealth - newHealth) << "%. Current Health: " << newHealth << "%\n";


    manager.pushCommand(shared_from_this());
}

void FreeRunwayCmd::undo() {
    if (targetFlight && targetRunway) {
        auto plane = targetFlight->getAircraft();
        auto& manager = AirportManager::getInstance();
        auto airline = manager.findAirlineByAircraft(plane->getId());


        if (airline) {
            airline->addFunds(calculatedTax);
            airline->deductFunds(revenue);
        }

        targetRunway->accommodateAircraft(plane);
        targetFlight->setStatus(FlightStatus::Boarding);

        std::cout << "[Undo Success] Runway R" << runwayId << " is occupied again. Flight " << targetFlight->getFlightId() << " reverted to Boarding.\n";
    }
}