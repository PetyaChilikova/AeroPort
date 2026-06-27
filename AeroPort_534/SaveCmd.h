#pragma once
#include "Command.h"
#include <sstream>

class SaveCmd : public Command {
public:
    SaveCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {} 
};