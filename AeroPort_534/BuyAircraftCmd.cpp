#include "BuyAircraftCmd.h"
#include "AirportManager.h"
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include <iostream>

BuyAircraftCmd::BuyAircraftCmd(std::stringstream& ss) {
	if (!(ss >> airlineName >> type >> model)) {
		isValid = false;
		return;
	}

	if (type != "PrivateJet") {
		if (!(ss >> capacityOrTonnage)) {
			isValid = false;
		}
	}
}

void BuyAircraftCmd::execute() {
	auto& manager = AirportManager::getInstance();

	auto currentUser = manager.getCurrentUser();
	if (!currentUser || currentUser->getRole() != Role::Admin) {
		std::cout << "[Error] Unauthorized! Only System Administrator can buy aircraft.\n";
		return;
	}

	if (!isValid) {
		std::cout << "[Error] Invalid aircraft purchase parameters.\n";
		return;
	}

	auto airline = manager.findAirline(airlineName);
	if (!airline) {
		std::cout << "[Error] Airline '" << airlineName << "' not found!\n";
		return;
	}

	const double AIRCRAFT_PRICE = 10000.0;
	if (airline->getBalance() < AIRCRAFT_PRICE) {
		std::cout << "[Error] Airline '" << airlineName << "' has insufficient funds! (Balance: "
			<< airline->getBalance() << " EUR, Required: 10000.00 EUR)\n";
		return;
	}

	static int globalAircraftIdCounter = 0;
	int generatedId = ++globalAircraftIdCounter;

	std::shared_ptr<Aircraft> newAircraft = nullptr;

	if (type == "PassengerPlane") {
		newAircraft = std::make_shared<PassengerPlane>(generatedId, model, capacityOrTonnage);
	}
	else if (type == "CargoPlane") {
		newAircraft = std::make_shared<CargoPlane>(generatedId, model, capacityOrTonnage);
	}
	else if (type == "PrivateJet") {
		newAircraft = std::make_shared<PrivateJet>(generatedId, model);
	}
	else {
		std::cout << "[Error] Unknown aircraft type: " << type << "\n";
		return;
	}

	if (newAircraft) {
		airline->deductFunds(AIRCRAFT_PRICE);
		airline->addAircraft(newAircraft);

		std::cout << "[System] Airline '" << airlineName << "' bought " << model
			<< " (ID: " << generatedId << ") for 10000.00 EUR.\n";
	}
}

void BuyAircraftCmd::undo() {

}