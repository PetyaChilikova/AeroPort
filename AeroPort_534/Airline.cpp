#include "Airline.h"
#include <iostream>

Airline::Airline(const std::string name, double balance) : name(name), balance(balance) {}

std::string Airline::getName() const {
	return name;
}

double Airline::getBalance() const {
	return balance;
}

void Airline::addFunds(double amount) {
	if (amount > 0.0) {
		balance += amount;
	}
}

bool Airline::deductFunds(double amount) {
	if (amount <= 0.0) {
		return false;
	}
	if (balance >= amount) {
		balance -= amount;
		return true;
	}
	return false;
}

void Airline::addAircraft(std::shared_ptr<Aircraft> aircraft) {
	if (aircraft) {
		fleet.push_back(aircraft);
	}
}

std::shared_ptr<Aircraft> Airline::removeAircraftFromFleet(int id) {
	for (auto it = fleet.begin(); it != fleet.end(); ++it) {
		if ((*it)->getId() == id) {
			std::shared_ptr<Aircraft> found = *it;
			fleet.erase(it);
			return found;
		}
	}
	return nullptr;
}

const std::vector<std::shared_ptr<Flight>>& Airline::getFlights() const {
	return organizedFlights;
}

void Airline::addFlight(std::shared_ptr<Flight> flight) {
	if (flight) {
		organizedFlights.push_back(flight);
	}
}

const std::vector<std::shared_ptr<Aircraft>>& Airline::getFleet() const {
	return fleet;
}

std::shared_ptr<Aircraft> Airline::findAircraftInFleet(int id) const {
	for (const auto& craft : fleet) {
		if (craft->getId() == id) {
			return craft;
		}
	}
	return nullptr;
}