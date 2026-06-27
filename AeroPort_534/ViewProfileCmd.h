#pragma once
#include "Command.h"
#include <sstream>

class ViewProfileCmd : public Command {
public:
    ViewProfileCmd(std::stringstream& ss) {}

    void execute() override;
    void undo() override;
};