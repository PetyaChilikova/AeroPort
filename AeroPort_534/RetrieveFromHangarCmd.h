#pragma once
#include "Command.h"
#include <sstream>

class RetrieveFromHangarCmd : public Command {
private:
    int aircraftId;

public:
    RetrieveFromHangarCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {} 
};