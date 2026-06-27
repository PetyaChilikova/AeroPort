#pragma once
#include "Command.h"
#include "Flight.h"
#include <sstream>
#include <string>
#include <memory>

class DelayFlightCmd : public Command {
private:
    std::string flightId;
    std::shared_ptr<Flight> targetFlight;
    FlightStatus previousStatus;

public:
    DelayFlightCmd(std::stringstream& ss);

    void execute() override;
    void undo() override;
};