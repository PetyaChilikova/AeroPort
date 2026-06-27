#pragma once
#include "Command.h"
#include <sstream>

class ListRunwaysCmd : public Command {
public:
    ListRunwaysCmd(std::stringstream& ss) {}

    void execute() override;
    void undo() override;
};