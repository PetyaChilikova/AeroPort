#pragma once
#include "Command.h"
#include <sstream>

class RegisterCmd : public Command {
private:
	std::string name;
	std::string password;
	std::string roleStr;

public:
	RegisterCmd(std::stringstream& ss);

	void execute() override;
	void undo() override;
};