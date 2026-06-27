#pragma once
#include "Command.h"
#include <string>
#include <sstream>

class RegisterAirlineCmd : public Command {
private:
	std::string airlineName;
	double initialCapital = 0.0;
	bool isValid = true;

public:
	RegisterAirlineCmd(std::stringstream& ss);

	void execute() override;
	void undo() override;
};
