#include "SendToHangarCmd.h"
#include "AirportManager.h"
#include <iostream>

SendToHangarCmd::SendToHangarCmd(std::stringstream& ss) : aircraftId(-1), hangarId("") {
    ss >> aircraftId >> hangarId;
}

void SendToHangarCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || currentUser->getRole() != Role::Admin) {
        std::cout << "[Error] Unauthorized! Only Admin can send aircraft to hangar.\n";
        return;
    }

    auto targetAircraft = manager.findAircraftGlobal(aircraftId);
    if (!targetAircraft) {
        std::cout << "[Error] Aircraft with ID " << aircraftId << " not found!\n";
        return;
    }

    auto targetHangar = manager.findHangar(hangarId);
    if (!targetHangar) {
        std::cout << "[Error] Hangar " << hangarId << " not found!\n";
        return;
    }

    if (targetHangar->isFull()) {
        std::cout << "[Error] Cannot send aircraft. Hangar " << hangarId << " is full!\n";
        return;
    }

    auto targetAirline = manager.findAirlineByAircraft(aircraftId);
    if (!targetAirline) {
        std::cout << "[Error] Owner airline not found for aircraft ID " << aircraftId << "!\n";
        return;
    }

    double fee = targetHangar->getRepairFee();

    if (targetAirline->getBalance() < fee) {
        std::cout << "[Error] Airline " << targetAirline->getName() << " cannot afford the repair fee of " << fee << " EUR!\n";
        return;
    }

    targetAirline->deductFunds(fee);
    if (targetHangar->addAircraft(targetAircraft)) {
        std::cout << "[System] Aircraft ID " << aircraftId << " sent to Hangar " << hangarId << ". Fee deducted: " << fee << " EUR.\n";
    }
}