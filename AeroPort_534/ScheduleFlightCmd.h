#pragma once
#include "Command.h"
#include <string>
#include <sstream>

class ScheduleFlightCmd : public Command {
private:
	std::string flightId;
	int aircraftId = 0;
	std::string destination;
	double basePrice = 0.0;
	bool isValid = true;

public:
	ScheduleFlightCmd(std::stringstream& ss);

	void execute() override;
	void undo() override;
};