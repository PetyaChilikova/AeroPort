#include "AssignRunwayCmd.h"
#include "AirportManager.h"
#include <iostream>

AssignRunwayCmd::AssignRunwayCmd(std::stringstream& ss) : runwayId(-1), previousFlightStatus(FlightStatus::Scheduled) {
    ss >> flightId;

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

void AssignRunwayCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || (currentUser->getRole() != Role::Dispatcher && currentUser->getRole() != Role::Admin)) {
        std::cout << "[Error] Unauthorized! Only Traffic Control can assign runways.\n";
        return;
    }

    targetFlight = manager.findFlight(flightId);
    if (!targetFlight) {
        std::cout << "[Error] Flight " << flightId << " not found!\n";
        return;
    }

    targetRunway = manager.findRunway(runwayId);
    if (!targetRunway) {
        std::cout << "[Error] Runway R" << runwayId << " not found!\n";
        return;
    }

    if (targetFlight->getStatus() != FlightStatus::Scheduled && targetFlight->getStatus() != FlightStatus::Delayed) {
        std::cout << "[Error] Flight " << flightId << " is not in a state to be assigned a runway!\n";
        return;
    }

    auto plane = targetFlight->getAircraft();
    if (!plane) {
        std::cout << "[Error] Flight " << flightId << " does not have an aircraft assigned!\n";
        return;
    }

    if (targetRunway->getStatus() == RunwayStatus::Occupied) {
        std::cout << "[Error] Runway R" << runwayId << " is currently Occupied by another aircraft!\n";
        return;
    }

    if (!targetRunway->canAccept(plane)) {
        std::cout << "[Error] Runway R" << runwayId << " does not meet aircraft requirements! ";
        std::cout << "(Length " << targetRunway->getLength() << "m";
        if (plane->getMinRunwayLength() > targetRunway->getLength()) {
            std::cout << " < " << plane->getMinRunwayLength() << "m";
        }
        if (plane->requiresHeavyDuty() && !targetRunway->hasHeavyDuty()) {
            std::cout << ". Missing HeavyDuty flag";
        }
        if (plane->requiresVIPTerminal() && !targetRunway->hasVIPTerminal()) {
            std::cout << ". Missing VIP flag";
        }
        std::cout << ").\n";
        return;
    }

    previousFlightStatus = targetFlight->getStatus();

    targetRunway->accommodateAircraft(plane);
    targetFlight->setStatus(FlightStatus::Boarding);

    std::cout << "[Success] Flight " << flightId << " assigned to R" << runwayId
        << ". Status -> Boarding. Runway R" << runwayId << " -> Occupied.\n";

    manager.pushCommand(shared_from_this());
}

void AssignRunwayCmd::undo() {
    if (targetFlight && targetRunway) {
        targetRunway->releaseRunway(); 

        std::cout << "[Undo Success] Runway assignment reverted. Flight " << flightId
            << " status reverted to Scheduled. Runway R" << runwayId << " is Free again.\n";
    }
}