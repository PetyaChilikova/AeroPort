#pragma once
#include <memory>
#include <string>
#include <sstream>
#include "Command.h"

class CommandFactory {
public:
    static std::shared_ptr<Command> createCommand(const std::string& name, std::stringstream& ss);
};
