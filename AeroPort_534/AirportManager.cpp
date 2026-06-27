#include "AirportManager.h"
#include "CommandFactory.h"
#include "Admin.h"
#include <iostream>
#include <sstream>

AirportManager::AirportManager() : currentUser(nullptr) {
	auto defaultAdmin = Admin::getInstance();
	allUsers.push_back(defaultAdmin);
}

AirportManager& AirportManager::getInstance() {
	static AirportManager instance;
	return instance;
}

void AirportManager::run() {
	std::string line;
	std::cout << "=== Airport Management System Engine Started ===\n";
	std::cout << "Type 'exit' to stop the application.\n\n";

	while (std::getline(std::cin, line)) {
		if (line == "exit" || line == "quit") {
			std::cout << "[System] Shutting down. Goodbye!\n";
			break;
		}

		std::stringstream ss(line);
		std::string commandName;
		ss >> commandName;

		if (commandName.empty()) {
			continue;
		}

		auto cmd = CommandFactory::createCommand(commandName, ss);

		if (cmd) {
			cmd->execute();
		}
		else {
			std::cout << "[Error] Unknown command or not implemented yet: " << commandName << "\n";
		}
	}
}

std::shared_ptr<User> AirportManager::getCurrentUser() const {
	return currentUser;
}

void AirportManager::setCurrentUser(std::shared_ptr<User> user) {
	currentUser = user;
}

void AirportManager::registerUser(std::shared_ptr<User> user) {
	if (user) {
		allUsers.push_back(user);
	}
}

void AirportManager::registerAirline(std::shared_ptr<Airline> airline) {
	if (airline) {
		allAirlines.push_back(airline);
	}
}

void AirportManager::addRunway(std::shared_ptr<Runway> runway) {
	if (runway) {
		allRunways.push_back(runway);
	}
}

void AirportManager::addHangar(std::shared_ptr<Hangar> hangar) {
	if (hangar) {
		allHangars.push_back(hangar);
	}
}

void AirportManager::addFlight(std::shared_ptr<Flight> flight) {
	if (flight) {
		allFlights.push_back(flight);
	}
}

std::shared_ptr<User> AirportManager::findUser(const std::string& username) const {
	for (const auto& user : allUsers) {
		if (user->getName() == username) {
			return user;
		}
	}
	return nullptr;
}

std::shared_ptr<Airline> AirportManager::findAirline(const std::string& name) const {
	for (const auto& airline : allAirlines) {
		if (airline->getName() == name) {
			return airline;
		}
	}
	return nullptr;
}

std::shared_ptr<Runway> AirportManager::findRunway(int id) const {
	for (const auto& runway : allRunways) {
		if (runway->getId() == id) {
			return runway;
		}
	}
	return nullptr;
}

std::shared_ptr<Hangar> AirportManager::findHangar(const std::string& id) const {
	for (const auto& hangar : allHangars) {
		if (hangar->getId() == id) {
			return hangar;
		}
	}
	return nullptr;
}

std::shared_ptr<Flight> AirportManager::findFlight(const std::string& id) const {
	for (const auto& flight : allFlights) {
		if (flight->getFlightId() == id) {
			return flight;
		}
	}
	return nullptr;
}

std::shared_ptr<Aircraft> AirportManager::findAircraftGlobal(int id) const {
	for (const auto& airline : allAirlines) {
		auto craft = airline->findAircraftInFleet(id);
		if (craft != nullptr) {
			return craft;
		}
	}
	return nullptr;
}

std::shared_ptr<Airline> AirportManager::findAirlineByAircraft(int aircraftId) const {
	for (const auto& airline : allAirlines) {
		auto craft = airline->findAircraftInFleet(aircraftId);
		if (craft != nullptr) {
			return airline; 
		}
	}
	return nullptr;
}

const std::vector<std::shared_ptr<Flight>>& AirportManager::getAllFlights() const {
	return allFlights;
}

const std::vector<std::shared_ptr<Runway>>& AirportManager::getAllRunways() const {
	return allRunways;
}

const std::vector<std::shared_ptr<Hangar>>& AirportManager::getAllHangars() const {
	return allHangars;
}

void AirportManager::pushCommand(std::shared_ptr<Command> cmd) {
	commandHistory.push(cmd);
}

void AirportManager::popAndUndo() {
	if (!commandHistory.empty()) {
		auto lastCmd = commandHistory.top();
		commandHistory.pop();
		lastCmd->undo();
	}
	else {
		std::cout << "[System] No dispatcher commands to undo.\n";
	}
}