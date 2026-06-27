#include "CloseRunwayCmd.h"
#include "AirportManager.h"
#include <iostream>

CloseRunwayCmd::CloseRunwayCmd(std::stringstream& ss) : runwayId(-1) {
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

void CloseRunwayCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || currentUser->getRole() != Role::Admin) {
        std::cout << "[Error] Unauthorized! Only Admin can close runways for maintenance.\n";
        return;
    }

    auto targetRunway = manager.findRunway(runwayId);
    if (!targetRunway) {
        std::cout << "[Error] Runway R" << runwayId << " not found!\n";
        return;
    }

    auto planeOnRunway = targetRunway->getCurrentAircraft();

    targetRunway->setMaintenance(true);

    if (targetRunway->getStatus() == RunwayStatus::Maintenance) {
        std::cout << "[System] Runway R" << runwayId << " status successfully changed to Maintenance.\n";

        if (planeOnRunway) {
            bool flightFound = false;
            for (const auto& flight : manager.getAllFlights()) {
                if (flight->getStatus() == FlightStatus::Boarding && flight->getAircraft() == planeOnRunway) {
                    flight->setStatus(FlightStatus::Scheduled);
                    std::cout << "[System] Flight " << flight->getFlightId() << " reverted from Boarding to Scheduled.\n";
                    flightFound = true;
                    break;
                }
            }

            targetRunway->releaseRunway();

            if (!flightFound) {
                std::cout << "[System] Aircraft ID " << planeOnRunway->getId() << " removed from runway, but no active boarding flight was found.\n";
            }
        }
    }
}