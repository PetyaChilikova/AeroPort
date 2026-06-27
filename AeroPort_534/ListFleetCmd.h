#pragma once
#include "Command.h"
#include <sstream>
#include <string>

class ListFleetCmd : public Command {
private:
    std::string airlineName;

public:
    ListFleetCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {} 
};