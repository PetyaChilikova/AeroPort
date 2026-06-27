#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Aircraft.h"
#include "Flight.h"

class Airline {
private:
	std::string name;
	double balance;
	std::vector<std::shared_ptr<Aircraft>> fleet;
	std::vector<std::shared_ptr<Flight>> organizedFlights;

public:
	Airline(const std::string name, double balance);

	std::string getName() const;
	double getBalance() const;

	void addFunds(double amount);
	bool deductFunds(double amount);

	void addAircraft(std::shared_ptr<Aircraft> aircraft);
	std::shared_ptr<Aircraft> removeAircraftFromFleet(int id);

	const std::vector<std::shared_ptr<Flight>>& getFlights() const;
	void addFlight(std::shared_ptr<Flight> flight);

	const std::vector<std::shared_ptr<Aircraft>>& getFleet() const;
	std::shared_ptr<Aircraft> findAircraftInFleet(int id) const;
};


