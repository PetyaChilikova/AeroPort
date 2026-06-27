#include "CloneAircraftCmd.h"
#include "AirportManager.h"
#include <iostream>
#include <iomanip>

CloneAircraftCmd::CloneAircraftCmd(std::stringstream& ss) : sourceAircraftId(-1), count(0) {
    ss >> sourceAircraftId >> count;
}

void CloneAircraftCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || currentUser->getRole() != Role::Admin) {
        std::cout << "[Error] Unauthorized! Only Admin can clone aircraft.\n";
        return;
    }

    if (count <= 0) {
        std::cout << "[Error] Count must be greater than 0.\n";
        return;
    }

    auto originalAircraft = manager.findAircraftGlobal(sourceAircraftId);
    if (!originalAircraft) {
        std::cout << "[Error] Aircraft with ID " << sourceAircraftId << " not found!\n";
        return;
    }

    auto airline = manager.findAirlineByAircraft(sourceAircraftId);
    if (!airline) {
        std::cout << "[Error] Owner airline not found for aircraft ID " << sourceAircraftId << "!\n";
        return;
    }

    int maxId = 0;
    for (int i = 1; i < 1000; i++) {
        if (manager.findAircraftGlobal(i)) {
            maxId = i;
        }
    }
    int nextId = maxId + 1;

    for (int i = 0; i < count; ++i) {
        std::shared_ptr<Aircraft> cloned = originalAircraft->clone();
        cloned->setId(nextId);
        cloned->repair();

        airline->addAircraft(cloned);

        auto oldFlags = std::cout.flags();
        std::cout << "[System] Aircraft ID: " << sourceAircraftId
            << " successfully cloned. New Aircraft ID: " << nextId
            << ". " << airline->getName() << " balance: "
            << std::fixed << std::setprecision(2) << airline->getBalance() << " EUR.\n";
        std::cout.flags(oldFlags);

        nextId++;
    }
}