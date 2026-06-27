#include "VIPTicket.h"
#include <string>

VIPTicket::VIPTicket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage) :
	Ticket(owner, flightId, paidAmount, luggage) { }

double VIPTicket::getPassengerCancellationRefund() const {
	return paidAmount;
}

double VIPTicket::getAdminCancellationRefund() const {
	return paidAmount;
}

TicketType VIPTicket::getType() const {
	return TicketType::VIP;
}