#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Aircraft.h"

enum class FlightStatus {
	Scheduled,
	Boarding,
	Departed,
	Delayed,
	Cancelled
};

class Ticket;

class Flight {
private:
	std::string flightId;
	std::string destination;
	FlightStatus status;
	std::shared_ptr<Aircraft> aircraft;
	double basePrice;
	std::vector<std::shared_ptr<Ticket>> soldTickets;

public:
	Flight(const std::string& id, const std::string& dest, std::shared_ptr<Aircraft> plane, double basePrice);
	void setStatus(FlightStatus status);
	FlightStatus getStatus() const;

	std::string getFlightId() const;
	std::shared_ptr<Aircraft> getAircraft() const;
	std::string getDestination() const;
	double getBasePrice() const;
	const std::vector<std::shared_ptr<Ticket>>& getTickets() const;

	bool bookTicket(std::shared_ptr<Ticket> ticket);
	bool cancelTicket(const std::string& passengerName);
};