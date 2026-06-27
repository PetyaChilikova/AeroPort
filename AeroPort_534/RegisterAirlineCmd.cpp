#include "RegisterAirlineCmd.h"
#include "AirportManager.h"
#include "Airline.h"
#include <iostream>
#include <iomanip>

RegisterAirlineCmd::RegisterAirlineCmd(std::stringstream& ss) {
	if (!(ss >> airlineName >> initialCapital)) {
		isValid = false;
	}
}

void RegisterAirlineCmd::execute() {
	auto& manager = AirportManager::getInstance();

	auto currentUser = manager.getCurrentUser();
	if (!currentUser || currentUser->getRole() != Role::Admin) {
		std::cout << "[Error] Unauthorized! Only System Administrator can register airlines.\n";
		return;
	}

	if (!isValid || airlineName.empty() || initialCapital < 0.0) {
		std::cout << "[Error] Invalid airline registration parameters.\n";
		return;
	}

	if (manager.findAirline(airlineName) != nullptr) {
		std::cout << "[Error] Airline '" << airlineName << "' already exists!\n";
		return;
	}

	auto newAirline = std::make_shared<Airline>(airlineName, initialCapital);
	manager.registerAirline(newAirline);

	auto oldFlags = std::cout.flags();
	std::cout << "[System] Airline '" << airlineName << "' registered successfully with initial capital "
		<< std::fixed << std::setprecision(2) << initialCapital << " EUR.\n";
	std::cout.flags(oldFlags);
}

void RegisterAirlineCmd::undo() {

}