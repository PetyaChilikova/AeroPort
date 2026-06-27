#pragma once
#include "Command.h"
#include "Flight.h"
#include "Runway.h"
#include <sstream>
#include <string>
#include <memory>

class AssignRunwayCmd : public Command {
private:
    std::string flightId;
    int runwayId;

    std::shared_ptr<Flight> targetFlight;
    std::shared_ptr<Runway> targetRunway;
    FlightStatus previousFlightStatus; 

public:
    AssignRunwayCmd(std::stringstream& ss);

    void execute() override;
    void undo() override;
};