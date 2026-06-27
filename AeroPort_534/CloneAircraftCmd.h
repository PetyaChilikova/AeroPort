#pragma once
#include "Command.h"
#include <sstream>

class CloneAircraftCmd : public Command {
private:
    int sourceAircraftId;
    int count;

public:
    CloneAircraftCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {}
};