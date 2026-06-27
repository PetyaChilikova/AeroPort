#include "LastMinuteTicket.h"
#include <string>

LastMinuteTicket::LastMinuteTicket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage):
	Ticket(owner, flightId, paidAmount, luggage) { }

double LastMinuteTicket::getPassengerCancellationRefund() const {
	return 0.0;
}

double LastMinuteTicket::getAdminCancellationRefund() const {
	return paidAmount;
}

TicketType LastMinuteTicket::getType() const {
	return TicketType::LastMinute;
}