#pragma once
#include "Command.h"
#include <string>
#include <sstream>

class BuildRunwayCmd : public Command {
private:
	std::string runwayIdStr;
	int length = 0;
	bool ils = false;
	bool vip = false;
	bool heavy = false;
	bool isValid = true;

public:
	BuildRunwayCmd(std::stringstream& ss);
	void execute() override;
	void undo() override;
};
