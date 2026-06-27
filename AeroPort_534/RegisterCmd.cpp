#include "RegisterCmd.h"
#include "AirportManager.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include <iostream>

RegisterCmd::RegisterCmd(std::stringstream& ss) {
	ss >> name >> password >> roleStr;
}

void RegisterCmd::execute() {
	if (name.empty() || password.empty() || roleStr.empty()) {
		std::cout << "[Error] Invalid registration!\n";
		return;
	}
	if (roleStr != "Passenger" && roleStr != "Dispatcher") {
		std::cout << "[System Error] Denied! You cannot register as Administrator!";
		return;
	}

	auto& manager = AirportManager::getInstance();

	std::shared_ptr<User> newUser = nullptr;
	if (roleStr == "Passenger") {
		newUser = std::make_shared<Passenger>(name, password);
	}
	else {
		newUser = std::make_shared<Dispatcher>(name, password);
	}
	manager.registerUser(newUser);
	std::cout << "[System] User '" << name << "' registered successfully (Role: " << roleStr << ").\n";
}

void RegisterCmd::undo() {

}
