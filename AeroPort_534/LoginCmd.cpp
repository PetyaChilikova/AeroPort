#include "LoginCmd.h"
#include "AirportManager.h"
#include <iostream>

LoginCmd::LoginCmd(std::stringstream& ss) {
	if (!(ss >> username >> password)) {
		isValid = false;
	}
}

void LoginCmd::execute() {
	auto& manager = AirportManager::getInstance();
	if (manager.getCurrentUser() != nullptr) {
		std::cout << "[System Error] A user is already logged in.\n";
		return;
	}
	if (!isValid || username.empty() || password.empty()) {
		std::cout << "[Eror] Invalid input.\n";
		return;
	}
	if (username == "admin" && password != "admin") {
		std::cout << "[Error] Invalid input.\n";
		return;
	}
	auto user = manager.findUser(username);
	if (user && user->checkPassword(password)) {
		manager.setCurrentUser(user);
		std::cout << "[System] Successfully logged in. Role: " << user->getRoleString() << ".\n";
		return;
	}
	std::cout << "[Error] Invalid input.\n";
}

void LoginCmd::undo() {

}