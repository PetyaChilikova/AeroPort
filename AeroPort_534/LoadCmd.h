#pragma once
#include "Command.h"
#include <sstream>

class LoadCmd : public Command {
public:
    LoadCmd(std::stringstream& ss);

    void execute() override;
    void undo() override {} 
};