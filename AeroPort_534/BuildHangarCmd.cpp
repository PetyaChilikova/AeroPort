#include "BuildHangarCmd.h"
#include "AirportManager.h"
#include "Hangar.h"
#include <iostream>
#include <iomanip>

BuildHangarCmd::BuildHangarCmd(std::stringstream& ss) {
	if (!(ss >> hangarId >> capacity >> repairFee)) {
		isValid = false;
	}
}

void BuildHangarCmd::execute() {
	auto& manager = AirportManager::getInstance();

	auto currentUser = manager.getCurrentUser();
	if (!currentUser || currentUser->getRole() != Role::Admin) {
		std::cout << "[Error] Unauthorized! Only System Administrator can build hangars.\n";
		return;
	}

	if (!isValid || hangarId.empty() || capacity <= 0 || repairFee < 0.0) {
		std::cout << "[Error] Invalid hangar specifications.\n";
		return;
	}

	if (manager.findHangar(hangarId) != nullptr) {
		std::cout << "[Error] Hangar " << hangarId << " already exists!\n";
		return;
	}

	auto newHangar = std::make_shared<Hangar>(hangarId, static_cast<size_t>(capacity), repairFee);

	manager.addHangar(newHangar);

	auto oldFlags = std::cout.flags();
	std::cout << "[System] Hangar " << hangarId << " built successfully (Capacity: " << capacity
		<< ", Repair Fee: " << std::fixed << std::setprecision(2) << repairFee << " EUR).\n";
	std::cout.flags(oldFlags); 
}

void BuildHangarCmd::undo() {

}