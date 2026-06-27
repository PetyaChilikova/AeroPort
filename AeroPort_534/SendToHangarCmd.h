#pragma once
#include "Command.h"
#include <sstream>

class SendToHangarCmd : public Command {
private:
    int aircraftId;
    std::string hangarId;

public:
    SendToHangarCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {}
};