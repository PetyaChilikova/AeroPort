#pragma once
#include "Ticket.h"
#include <string>

class VIPTicket : public Ticket {
public:
	VIPTicket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage = 20.0);

	double getPassengerCancellationRefund() const override;
	double getAdminCancellationRefund() const override;
	TicketType getType() const override;
};
