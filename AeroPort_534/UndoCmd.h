#pragma once
#include "Command.h"
#include <sstream>

class UndoCmd : public Command {
public:
    UndoCmd(std::stringstream& ss) {}

    void execute() override;
    void undo() override;
};