#include "BookTicketCmd.h"
#include "AirportManager.h"
#include "TicketFactory.h"
#include "Flight.h"
#include <iostream>
#include <stdexcept>

BookTicketCmd::BookTicketCmd(std::stringstream& ss) {
    if (!(ss >> flightId >> ticketTypeStr)) {
        isValid = false;
    }
    ss >> luggage; 
}

void BookTicketCmd::execute() {
    auto& manager = AirportManager::getInstance();

    auto currentUser = manager.getCurrentUser();
    if (!currentUser) {
        std::cout << "[Error] You must be logged in to book a ticket!\n";
        return;
    }
    if (currentUser->getRole() != Role::Passenger) {
        std::cout << "[Error] Only Passengers can book tickets!\n";
        return;
    }

    if (!isValid || flightId.empty() || ticketTypeStr.empty()) {
        std::cout << "[Error] Invalid parameters. Usage: book-ticket <flightId> <type> [luggage]\n";
        return;
    }

    auto flight = manager.findFlight(flightId);
    if (!flight) {
        std::cout << "[Error] Flight with ID " << flightId << " not found!\n";
        return;
    }

    try {
        TicketType type = TicketFactory::strToType(ticketTypeStr);

        std::string owner = currentUser->getName();
        double basePrice = flight->getBasePrice();

        bool isCargo = false;

        auto newTicket = TicketFactory::create(type, owner, flightId, basePrice, luggage, isCargo);

        if (flight->bookTicket(newTicket)) {
            std::cout << "[System] " << owner << " successfully booked a " << ticketTypeStr
                << " ticket for flight " << flightId << ".\n";
        }
        else {
            std::cout << "[Error] Could not book ticket. Flight might be full or closed.\n";
        }
    }
    catch (const std::invalid_argument& e) {
        std::cout << "[Error] " << e.what() << "\n";
    }
}

void BookTicketCmd::undo() {
}