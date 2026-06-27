#pragma once
#include "Command.h"
#include <string>
#include <sstream>

class BookTicketCmd : public Command {
private:
    std::string flightId;
    std::string ticketTypeStr;
    double luggage = 0.0;
    bool isValid = true;

public:
    BookTicketCmd(std::stringstream& ss);

    void execute() override;
    void undo() override;
};
