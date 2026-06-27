#pragma once
#include "Command.h"
#include <string>
#include <sstream>

class BuyAircraftCmd : public Command {
private:
	std::string airlineName;
	std::string type;
	std::string model;
	int capacityOrTonnage = 0;
	bool isValid = true;

public:
	BuyAircraftCmd(std::stringstream& ss);

	void execute() override;
	void undo() override;
};