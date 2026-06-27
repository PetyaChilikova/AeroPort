#pragma once
#include "Ticket.h"
#include <string>

class LastMinuteTicket : public Ticket {
public:
	LastMinuteTicket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage = 0.0);

	double getPassengerCancellationRefund() const override;
	double getAdminCancellationRefund() const override;
	TicketType getType() const override;
};
