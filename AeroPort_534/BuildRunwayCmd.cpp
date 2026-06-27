#include "BuildRunwayCmd.h"
#include "AirportManager.h"
#include "Runway.h"
#include <iostream>

BuildRunwayCmd::BuildRunwayCmd(std::stringstream& ss) {
	if (!(ss >> runwayIdStr >> length)) {
		isValid = false;
		return;
	}

	std::string flag;
	while (ss >> flag) {
		if (flag == "ILS") {
			ils = true;
		}
		if (flag == "VIP") {
			vip = true;
		}
		if (flag == "HeavyDuty") {
			heavy = true;
		}
	}
}

void BuildRunwayCmd::execute() {
	auto& manager = AirportManager::getInstance();

	auto currentUser = manager.getCurrentUser();
	if (!currentUser || currentUser->getRole() != Role::Admin) {
		std::cout << "[Error] Unauthorized! Only System Administrator can build runways!\n";
		return;
	}

	if (!isValid || length <= 0 || runwayIdStr[0] != 'R') {
		std::cout << "[Error] Invalid input!\n";
		return;
	}

	int numericId = std::stoi(runwayIdStr.substr(1));
	if (manager.findRunway(numericId) != nullptr) {
		std::cout << "[Error] Runway already exists!\n";
		return;
	}

	auto newRunway = std::make_shared<Runway>(numericId, length, ils, vip, heavy);

	manager.addRunway(newRunway);

	std::string attrStr = "Basic";
	if (ils && heavy) {
		attrStr = "ILS, HeavyDuty";
	}
	else if (vip) {
		attrStr = "VIP Terminal";
	}
	else if (heavy) {
		attrStr = "HeavyDuty";
	}
	std::cout << "[System] Runway " << runwayIdStr << " (" << length << "m, " << attrStr << ") built successfully.\n";
}

void BuildRunwayCmd::undo() {

}