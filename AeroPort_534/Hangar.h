#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Aircraft.h"

class Hangar {
private:
	std::string id;
	size_t capacity;
	double repairFee;

	std::vector<std::shared_ptr<Aircraft>> parkedAircrafts;

public:
	Hangar(const std::string& id, size_t capacity, double repairFee);

	std::string getId() const;
	size_t getCapacity() const;
	double getRepairFee() const;

	size_t getCurrentOccupancy() const;
	bool isFull() const;

	bool addAircraft(std::shared_ptr<Aircraft> aircraft);
	std::shared_ptr<Aircraft> removeAircraft(int aircraftId);
	bool containsAircraft(int aircraftId) const;

	std::shared_ptr<Aircraft> getAircraft(int aircraftId) const;
};
