#pragma once
#include "Command.h"
#include <string>
#include <sstream>

class BuildHangarCmd : public Command {
private:
	std::string hangarId;
	int capacity = 0;
	double repairFee = 0.0;
	bool isValid = true;

public:
	BuildHangarCmd(std::stringstream& ss);

	void execute() override;
	void undo() override; 
};