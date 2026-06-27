#pragma once
#include <memory>
#include <string>
#include "Ticket.h"

class TicketFactory {
public:
	static std::shared_ptr<Ticket> create(TicketType type, const std::string& owner,
		const std::string& flightId, double basePrice, double luggage = 0.0, bool isCargoReservation = false);
	static TicketType strToType(const std::string& typeStr);
	static std::string typeToStr(TicketType type);
};

