#include "CancelFlightCmd.h"
#include "AirportManager.h"
#include "Ticket.h"
#include "Passenger.h" 
#include <iostream>
#include <iomanip>

CancelFlightCmd::CancelFlightCmd(std::stringstream& ss) : flightId("") {
    ss >> flightId;
}

void CancelFlightCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser || currentUser->getRole() != Role::Admin) {
        std::cout << "[Error] Unauthorized! Only Admin can cancel flights.\n";
        return;
    }

    auto targetFlight = manager.findFlight(flightId);
    if (!targetFlight) {
        std::cout << "[Error] Flight " << flightId << " not found!\n";
        return;
    }

    if (targetFlight->getStatus() == FlightStatus::Departed) {
        std::cout << "[Error] Flight " << flightId << " has already Departed. It cannot be cancelled.\n";
        return;
    }

    if (targetFlight->getStatus() == FlightStatus::Cancelled) {
        std::cout << "[Warning] Flight " << flightId << " is already cancelled.\n";
        return;
    }

    auto plane = targetFlight->getAircraft();
    std::shared_ptr<Airline> airline = nullptr;
    if (plane) {
        airline = manager.findAirlineByAircraft(plane->getId());
    }

    double totalRefund = 0.0;
    const auto& tickets = targetFlight->getTickets();

    auto ticketsCopy = tickets;

    for (const auto& ticket : ticketsCopy) {
        double refundAmount = ticket->getAdminCancellationRefund();
        totalRefund += refundAmount;

        auto user = manager.findUser(ticket->getOwnerName());
        if (user && user->getRole() == Role::Passenger) {
            auto passenger = std::dynamic_pointer_cast<Passenger>(user);
            if (passenger) {
                passenger->addFunds(refundAmount);
                passenger->removeTicket(ticket);
            }
        }
    }

    if (airline) {
        airline->deductFunds(totalRefund);
    }

    targetFlight->setStatus(FlightStatus::Cancelled);

    std::cout << "[System] Flight " << flightId << " has been successfully cancelled.\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[Finance] Total refund of " << totalRefund << " EUR distributed to passengers.\n";
}