#include "TicketFactory.h"
#include <stdexcept>
#include "StandardTicket.h"
#include "VIPTicket.h"
#include "LastMinuteTicket.h"

std::shared_ptr<Ticket> TicketFactory::create(TicketType type, const std::string& owner,
	const std::string& flightId, double basePrice, double luggage, bool isCargoReservation) {
	if (isCargoReservation && type != TicketType::Standard) {
		throw std::invalid_argument("Cargo flights can only have Standard ticket!");
	}

	switch (type) {
	case TicketType::Standard: {
		if (isCargoReservation) {
			return std::make_shared<StandardTicket>(owner, flightId, basePrice, 1000.0, true);
		}
		return std::make_shared<StandardTicket>(owner, flightId, basePrice, luggage, false);
	}
	case TicketType::VIP: {
		double vipPrice = basePrice * 2.0;
		return std::make_shared<VIPTicket>(owner, flightId, vipPrice, luggage == 0.0 ? 20.0 : luggage);
	}
	case TicketType::LastMinute: {
		double lmPrice = basePrice * 0.5;
		return std::make_shared<LastMinuteTicket>(owner, flightId, lmPrice, luggage);
	}
	default:
		throw std::invalid_argument("Unknown ticket type!");
	}
}

TicketType TicketFactory::strToType(const std::string& typeStr) {
	if (typeStr == "Standard") {
		return TicketType::Standard;
	}
	if (typeStr == "VIP") {
		return TicketType::VIP;
	}
	if (typeStr == "LastMinute") {
		return TicketType::LastMinute;
	}
	throw std::invalid_argument("Invalid ticket type string: " + typeStr);
}

std::string TicketFactory::typeToStr(TicketType type) {
	switch (type) {
	case TicketType::Standard:
		return "Standard";
	case TicketType::VIP:
		return "VIP";
	case TicketType::LastMinute:
		return "LastMinute";
	default:
		return "Unknown";
	}
}