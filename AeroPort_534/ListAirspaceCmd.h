#pragma once
#include "Command.h"
#include <sstream>

class ListAirspaceCmd : public Command {
public:
    ListAirspaceCmd(std::stringstream& ss) {}

    void execute() override;
    void undo() override;
};