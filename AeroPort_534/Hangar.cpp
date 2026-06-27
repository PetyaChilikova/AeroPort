#include "Hangar.h"
#include <iostream>

Hangar::Hangar(const std::string& id, size_t capacity, double repairFee) : id(id), capacity(capacity), repairFee(repairFee){}
std::string Hangar::getId() const {
	return id;
}

size_t Hangar::getCapacity() const {
	return capacity;
}

double Hangar::getRepairFee() const {
	return repairFee;
}

size_t Hangar::getCurrentOccupancy() const {
	return parkedAircrafts.size();
}

bool Hangar::isFull() const {
	return parkedAircrafts.size() >= capacity;
}

bool Hangar::addAircraft(std::shared_ptr<Aircraft> aircraft) {
	if (!aircraft) {
		return false;
	}
	if (isFull()) {
		std::cout << "Error! Hangar " << id << " is full!" << std::endl;
		return false;
	}
	parkedAircrafts.push_back(aircraft);
	return true;
}

std::shared_ptr<Aircraft> Hangar::removeAircraft(int aircraftId) {
	for (auto it = parkedAircrafts.begin(); it != parkedAircrafts.end(); it++) {
		if ((*it)->getId() == aircraftId) {
			std::shared_ptr<Aircraft> current = *it;
			current->repair();
			parkedAircrafts.erase(it);
			return current;
		}
	}
	return nullptr;
}

std::shared_ptr<Aircraft> Hangar::getAircraft(int aircraftId) const {
	for (const auto& plane : parkedAircrafts) {
		if (plane->getId() == aircraftId) {
			return plane;
		}
	}
	return nullptr;
}

bool Hangar::containsAircraft(int aircraftId) const {
	return getAircraft(aircraftId) != nullptr;
}