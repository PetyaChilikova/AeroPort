#include "RetrieveFromHangarCmd.h"
#include "AirportManager.h"
#include <iostream>

RetrieveFromHangarCmd::RetrieveFromHangarCmd(std::stringstream& ss) : aircraftId(-1) {
    ss >> aircraftId;
}

void RetrieveFromHangarCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || currentUser->getRole() != Role::Admin) {
        std::cout << "[Error] Unauthorized! Only Admin can retrieve aircraft from hangar.\n";
        return;
    }

    std::shared_ptr<Hangar> sourceHangar = nullptr;
    for (const auto& hangar : manager.getAllHangars()) {
        if (hangar->containsAircraft(aircraftId)) {
            sourceHangar = hangar;
            break;
        }
    }

    if (!sourceHangar) {
        std::cout << "[Error] Aircraft ID " << aircraftId << " is not parked in any hangar!\n";
        return;
    }

    auto retrievedAircraft = sourceHangar->removeAircraft(aircraftId);

    if (retrievedAircraft) {
        std::cout << "[System] Aircraft ID " << aircraftId << " successfully retrieved from Hangar " << sourceHangar->getId() << ". Health restored to 100%.\n";
    }
}