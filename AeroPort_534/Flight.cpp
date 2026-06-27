#include "Flight.h"
#include "Ticket.h"
#include <iostream>

Flight::Flight(const std::string& id, const std::string& dest, std::shared_ptr<Aircraft> plane, double basePrice) : 
				flightId(id), destination(dest), aircraft(plane), basePrice(basePrice), status(FlightStatus::Scheduled){}

void Flight::setStatus(FlightStatus status) {
	this->status = status;
}

FlightStatus Flight::getStatus() const{
	return status;
}

std::string Flight::getFlightId() const {
	return flightId;
}

std::shared_ptr<Aircraft> Flight::getAircraft() const {
	return aircraft;
}

std::string Flight::getDestination() const {
	return destination;
}

double Flight::getBasePrice() const {
	return basePrice;
}

const std::vector<std::shared_ptr<Ticket>>& Flight::getTickets() const {
	return soldTickets;
}

bool Flight::bookTicket(std::shared_ptr<Ticket> ticket) {
	if (!ticket) {
		return false;
	}
	if (status != FlightStatus::Scheduled) {
		std::cout << "Error: cannot book ticket!" << std::endl;
		return false;
	}
	soldTickets.push_back(ticket);
	return true;
}

bool Flight::cancelTicket(const std::string& passengerName) {
	if (status != FlightStatus::Scheduled) {
		std::cout << "Error: you cannot cancel your ticket at this point!" << std::endl;
		return false;
	}

	for (auto it = soldTickets.begin(); it != soldTickets.end(); it++) {
		if ((*it)->getOwnerName() == passengerName) {
			soldTickets.erase(it);
			return true;
		}
	}
	return false;
}