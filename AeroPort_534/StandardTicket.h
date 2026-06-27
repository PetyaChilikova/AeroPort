#pragma once
#include "Ticket.h"
#include <string>

class StandardTicket : public Ticket {
private:
	bool isCargoReservation;
public:
	StandardTicket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage = 0.0, bool isCargoReservation = false);

	double getPassengerCancellationRefund() const override;
	double getAdminCancellationRefund() const override;
	TicketType getType() const override;
};
