#pragma once
#include "Command.h"
#include "Flight.h"
#include "Runway.h"
#include <sstream>
#include <string>
#include <memory>

class FreeRunwayCmd : public Command {
private:
    int runwayId;
    std::shared_ptr<Flight> targetFlight;
    std::shared_ptr<Runway> targetRunway;

    double calculatedTax;
    double revenue;

public:
    FreeRunwayCmd(std::stringstream& ss);

    void execute() override;
    void undo() override;
};