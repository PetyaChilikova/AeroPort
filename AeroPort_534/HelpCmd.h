#pragma once
#include "Command.h"
#include <sstream>

class HelpCmd : public Command {
public:
    HelpCmd(std::stringstream& ss) {}

    void execute() override;
    void undo() override;
};
