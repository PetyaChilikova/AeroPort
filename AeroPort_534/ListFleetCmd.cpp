#include "ListFleetCmd.h"
#include "AirportManager.h"
#include <iostream>

ListFleetCmd::ListFleetCmd(std::stringstream& ss) : airlineName("") {
    ss >> airlineName;
}

void ListFleetCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || currentUser->getRole() != Role::Admin) {
        std::cout << "[Error] Unauthorized! Only Admin can view airline fleets.\n";
        return;
    }

    auto airline = manager.findAirline(airlineName);
    if (!airline) {
        std::cout << "[Error] Airline \"" << airlineName << "\" not found!\n";
        return;
    }

    std::cout << "Fleet Overview for " << airlineName << ":\n";

    auto fleet = airline->getFleet();

    if (fleet.empty()) {
        std::cout << "No aircraft in this fleet.\n";
    }
    else {
        int counter = 1;
        for (const auto& aircraft : fleet) {
            std::cout << counter << ". " << aircraft->getType()
                << " (ID: " << aircraft->getId() << ") - "
                << "Health: " << aircraft->getHealth() << "%\n";
            counter++;
        }
    }
}