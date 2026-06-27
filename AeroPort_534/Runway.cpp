#include "Runway.h"
#include <iostream>

Runway::Runway(int id, int length, bool ILS, bool VIPTerminal, bool HeavyDuty) : 
	id(id), length(length), ILS(ILS), VIPTerminal(VIPTerminal), HeavyDuty(HeavyDuty), status(RunwayStatus::Free), currentAircraft(nullptr){}

int Runway::getId() const {
	return id;
}

int Runway::getLength() const {
	return length;
}

RunwayStatus Runway::getStatus() const {
	return status;
}

std::shared_ptr<Aircraft> Runway::getCurrentAircraft() const {
	return currentAircraft;
}

bool Runway::hasILS() const {
	return ILS;
}

bool Runway::hasVIPTerminal() const {
	return VIPTerminal;
}

bool Runway::hasHeavyDuty() const {
	return HeavyDuty;
}

bool Runway::canAccept(std::shared_ptr<Aircraft> aircraft) const {
	if (status != RunwayStatus::Free) {
		return false;
	}
	if (length < aircraft->getMinRunwayLength()) {
		return false;
	}
	if (aircraft->requiresHeavyDuty() && !HeavyDuty) {
		return false;
	}
	if (aircraft->requiresVIPTerminal() && !VIPTerminal) {
		return false;
	}
	return true;
}

bool Runway::accommodateAircraft(std::shared_ptr<Aircraft> aircraft) {
	if (canAccept(aircraft)) {
		currentAircraft = aircraft;
		status = RunwayStatus::Occupied;
		return true;
	}
	return false;
}

void Runway::releaseRunway() {
	currentAircraft = nullptr;
	status = RunwayStatus::Free;
}

void Runway::setMaintenance(bool needsMaintenance) {
	if (needsMaintenance) {
		status = RunwayStatus::Maintenance;
	}
	else {
		if (status == RunwayStatus::Maintenance) {
			status = RunwayStatus::Free;
		}
	}
}