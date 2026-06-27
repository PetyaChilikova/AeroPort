#pragma once
#include <memory>

class Command : public std::enable_shared_from_this<Command> {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
	virtual void undo() = 0;
};