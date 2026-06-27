#include "SetWeatherCmd.h"
#include "AirportManager.h"
#include "Ticket.h"
#include "Passenger.h"
#include "Runway.h"
#include <iostream>
#include <iomanip>

SetWeatherCmd::SetWeatherCmd(std::stringstream& ss) : newWeather("") {
    ss >> newWeather;
}

void SetWeatherCmd::attach(std::shared_ptr<WeatherObserver> observer) {
    if (observer) {
        observers.push_back(observer);
    }
}

void SetWeatherCmd::notifyObservers() {
    for (const auto& observer : observers) {
        observer->updateWeather(newWeather);
    }
}

void FlightWeatherWatch::updateWeather(const std::string& newWeather) {
    if (newWeather == "STORM" && flight->getStatus() == FlightStatus::Scheduled) {
        auto& manager = AirportManager::getInstance();

        std::cout << "[Observer] Flight " << flight->getFlightId() << " Cancelled due to severe weather!\n";
        std::cout << "[System] Auto-refunding passengers for flight " << flight->getFlightId() << "...\n";

        double totalRefund = 0.0;
        auto ticketsCopy = flight->getTickets();

        std::shared_ptr<Airline> airline = nullptr;
        if (flight->getAircraft()) {
            airline = manager.findAirlineByAircraft(flight->getAircraft()->getId());
        }

        for (const auto& ticket : ticketsCopy) {
            double refundAmount = ticket->getAdminCancellationRefund();
            totalRefund += refundAmount;

            auto user = manager.findUser(ticket->getOwnerName());
            if (user && user->getRole() == Role::Passenger) {
                auto passenger = std::dynamic_pointer_cast<Passenger>(user);
                if (passenger) {
                    std::cout << "[System] Auto-refunding " << std::fixed << std::setprecision(2)
                        << refundAmount << " EUR to passenger " << passenger->getName() << "...\n";

                    passenger->addFunds(refundAmount);
                    passenger->removeTicket(ticket);
                }
            }
        }

        if (airline) {
            airline->deductFunds(totalRefund);
        }

        flight->setStatus(FlightStatus::Cancelled);
    }
}

void SetWeatherCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || currentUser->getRole() != Role::Admin) {
        std::cout << "[Error] Unauthorized! Only Admin can change weather conditions.\n";
        return;
    }

    std::cout << "[ALERT] Global Weather Conditions changed to " << newWeather << "!\n";

    if (newWeather == "STORM") {
        std::cout << "[Observer] Verifying airport infrastructure for safe landing conditions...\n";

        bool hasActiveILSRunway = false;
        int maintenanceRunwayId = -1;

        for (const auto& runway : manager.getAllRunways()) {
            if (runway->getStatus() != RunwayStatus::Maintenance) {
                if (runway->hasILS()) {
                    hasActiveILSRunway = true;
                    break;
                }
            }
            else {
                maintenanceRunwayId = runway->getId();
            }
        }

        if (!hasActiveILSRunway) {
            std::cout << "[System] WARNING: No active runways with ILS available! ";
            if (maintenanceRunwayId != -1) {
                std::cout << "(R" << maintenanceRunwayId << " is currently in Maintenance).";
            }
            std::cout << "\n";

            for (const auto& flight : manager.getAllFlights()) {
                if (flight->getStatus() == FlightStatus::Scheduled) {
                    auto watch = std::make_shared<FlightWeatherWatch>(flight);
                    this->attach(watch);
                }
            }

            this->notifyObservers();
        }
    }
    else {
        std::cout << "[System] Weather is clear. All airport operations normal.\n";
    }
}