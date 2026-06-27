#include "StandardTicket.h"
#include <string>

StandardTicket::StandardTicket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage, bool isCargoReservation) :
	Ticket(owner, flightId, paidAmount, luggage), isCargoReservation(isCargoReservation) {
	if (isCargoReservation) {
		luggageWeight = 1000.0;
	}
}

double StandardTicket::getPassengerCancellationRefund() const {
	return paidAmount;
}

double StandardTicket::getAdminCancellationRefund() const {
	return paidAmount;
}

TicketType StandardTicket::getType() const {
	return TicketType::Standard;
}