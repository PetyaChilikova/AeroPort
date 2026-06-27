#pragma once
#include "Command.h"
#include <sstream>
#include <string>

class CancelFlightCmd : public Command {
private:
    std::string flightId;

public:
    CancelFlightCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {}
};