#pragma once
#include <string>
#include <memory>
#include "Aircraft.h"

enum class RunwayStatus {
	Free,
	Occupied,
	Maintenance
};

class Runway {
private:
	int id;
	int length;
	RunwayStatus status;
	bool ILS;
	bool VIPTerminal;
	bool HeavyDuty;
	std::shared_ptr<Aircraft> currentAircraft;
public:
	Runway(int id, int length, bool ILS, bool VIPTerminal, bool HeavyDuty);

	int getId() const;
	int getLength() const;
	RunwayStatus getStatus() const;
	std::shared_ptr<Aircraft> getCurrentAircraft() const;

	bool hasILS() const;
	bool hasVIPTerminal() const;
	bool hasHeavyDuty() const;

	bool canAccept(std::shared_ptr<Aircraft> aircraft) const;
	bool accommodateAircraft(std::shared_ptr<Aircraft> aircraft);
	void releaseRunway();
	void setMaintenance(bool needsMaintenance);
};
