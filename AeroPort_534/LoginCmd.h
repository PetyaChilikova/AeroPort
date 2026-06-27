#pragma once
#include "Command.h"
#include <string>
#include <sstream>

class LoginCmd : public Command {
private:
	std::string username;
	std::string password;
	bool isValid = true;
public:
	LoginCmd(std::stringstream& ss);
	void execute() override;
	void undo() override;
};