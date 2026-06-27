#pragma once
#include "Command.h"
#include <sstream>

class CloseRunwayCmd : public Command {
private:
    int runwayId;

public:
    CloseRunwayCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {}
};