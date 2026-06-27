#include "ListAirspaceCmd.h"
#include "AirportManager.h"
#include <iostream>

void ListAirspaceCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || (currentUser->getRole() != Role::Dispatcher && currentUser->getRole() != Role::Admin)) {
        std::cout << "[Error] Unauthorized! Only Traffic Control can view airspace.\n";
        return;
    }

    std::cout << "Pending Airspace Traffic (Scheduled / Delayed):\n";
    bool found = false;
    int counter = 1;

    const auto& flights = manager.getAllFlights();

    for (const auto& flight : flights) {
        if (flight->getStatus() == FlightStatus::Scheduled || flight->getStatus() == FlightStatus::Delayed) {

            std::string planeType = "UnknownPlane";
            auto plane = flight->getAircraft();

            if (plane) {
                planeType = plane->getType();
            }

            std::cout << counter << ". " << flight->getFlightId()
                << " [" << planeType << "] - " << flight->getDestination() << "\n";

            found = true;
            counter++;
        }
    }

    if (!found) {
        std::cout << "[System] No pending airspace traffic.\n";
    }
}

void ListAirspaceCmd::undo() {
}