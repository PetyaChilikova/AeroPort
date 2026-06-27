#pragma once
#include "Command.h"
#include <sstream>

class LogoutCmd : public Command {
public:
    LogoutCmd(std::stringstream& ss) {} 

    void execute() override;
    void undo() override;
};
