#include "ListRunwaysCmd.h"
#include "AirportManager.h"
#include <iostream>

void ListRunwaysCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || (currentUser->getRole() != Role::Dispatcher && currentUser->getRole() != Role::Admin)) {
        std::cout << "[Error] Unauthorized! Only Traffic Control can view runway statuses.\n";
        return;
    }

    std::cout << "Airport Runways Overview:\n";

    const auto& runways = manager.getAllRunways();

    if (runways.empty()) {
        std::cout << "[System] No runways have been built yet.\n";
        return;
    }

    for (const auto& runway : runways) {
        std::string features = "";

        if (runway->hasILS()) features += "ILS, ";
        if (runway->hasHeavyDuty()) features += "HeavyDuty, ";
        if (runway->hasVIPTerminal()) features += "VIP, ";

        if (features.empty()) {
            features = "Basic";
        }
        else {
            features = features.substr(0, features.length() - 2);
        }

        std::string statusText = "Unknown";
        switch (runway->getStatus()) {
        case RunwayStatus::Free:        statusText = "Free"; break;
        case RunwayStatus::Occupied:    statusText = "Occupied"; break;
        case RunwayStatus::Maintenance: statusText = "Maintenance"; break;
        }

        std::cout << "- R" << runway->getId()
            << " (" << runway->getLength() << "m, " << features
            << ") -> Status: " << statusText << "\n";
    }
}

void ListRunwaysCmd::undo() {
}