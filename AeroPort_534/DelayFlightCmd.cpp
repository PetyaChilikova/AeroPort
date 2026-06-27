#include "DelayFlightCmd.h"
#include "AirportManager.h"
#include <iostream>

DelayFlightCmd::DelayFlightCmd(std::stringstream& ss) : previousStatus(FlightStatus::Scheduled) {
    ss >> flightId;
}

void DelayFlightCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || (currentUser->getRole() != Role::Dispatcher && currentUser->getRole() != Role::Admin)) {
        std::cout << "[Error] Unauthorized! Only Traffic Control can delay flights.\n";
        return;
    }

    targetFlight = manager.findFlight(flightId);
    if (!targetFlight) {
        std::cout << "[Error] Flight " << flightId << " not found!\n";
        return;
    }

    if (targetFlight->getStatus() != FlightStatus::Scheduled && targetFlight->getStatus() != FlightStatus::Boarding) {
        std::cout << "[Error] Flight " << flightId << " cannot be delayed because it is already departed or cancelled!\n";
        return;
    }

    previousStatus = targetFlight->getStatus();
    targetFlight->setStatus(FlightStatus::Delayed);

    std::cout << "[Success] Flight " << flightId << " is now Delayed.\n";

    manager.pushCommand(shared_from_this());
}

void DelayFlightCmd::undo() {
    if (targetFlight) {
        targetFlight->setStatus(previousStatus);

        std::string statusStr = (previousStatus == FlightStatus::Boarding) ? "Boarding" : "Scheduled";
        std::cout << "[Undo Success] Delay cancelled. Flight " << flightId
            << " status reverted back to " << statusStr << ".\n";
    }
}