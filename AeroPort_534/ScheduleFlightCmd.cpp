#include "ScheduleFlightCmd.h"
#include "AirportManager.h"
#include "Flight.h"
#include "Airline.h"
#include <iostream>

ScheduleFlightCmd::ScheduleFlightCmd(std::stringstream& ss) {
	if (!(ss >> flightId >> aircraftId >> destination >> basePrice)) {
		isValid = false;
	}
}

void ScheduleFlightCmd::execute() {
	auto& manager = AirportManager::getInstance();

	auto currentUser = manager.getCurrentUser();
	if (!currentUser || currentUser->getRole() != Role::Admin) {
		std::cout << "[Error] Unauthorized! Only System Administrator can schedule flights.\n";
		return;
	}

	if (!isValid || flightId.empty() || destination.empty() || basePrice <= 0.0) {
		std::cout << "[Error] Invalid flight schedule parameters.\n";
		return;
	}

	if (manager.findFlight(flightId) != nullptr) {
		std::cout << "[Error] Flight " << flightId << " already exists!\n";
		return;
	}

	std::shared_ptr<Aircraft> targetAircraft = nullptr;
	std::shared_ptr<Airline> owningAirline = nullptr;

	targetAircraft = manager.findAircraftGlobal(aircraftId);

	if (!targetAircraft) {
		std::cout << "[Error] Aircraft with ID " << aircraftId << " not found in any airline!\n";
		return;
	}
	if (!targetAircraft->canFly()) {
		std::cout << "[Error] Cannot schedule flight! Aircraft ID " << aircraftId
			<< " requires maintenance (Health: " << targetAircraft->getHealth() << "%).\n";
		return;
	}

	auto newFlight = std::make_shared<Flight>(flightId, destination, targetAircraft, basePrice);

	manager.addFlight(newFlight);

	std::cout << "[System] Flight " << flightId << " to " << destination
			<< " scheduled successfully using Aircraft ID " << aircraftId << ".\n";
}

void ScheduleFlightCmd::undo() {
}