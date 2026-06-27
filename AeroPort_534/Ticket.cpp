#include "Ticket.h"
#include <string>

Ticket::Ticket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage) : 
				ownerName(owner), flightId(flightId), paidAmount(paidAmount), luggageWeight(luggage){}

std::string Ticket::getOwnerName() const {
	return ownerName;
}

std::string Ticket::getFlightId() const {
	return flightId;
}

double Ticket::getPaidAmount() const {
	return paidAmount;
}

double Ticket::getLuggageWeight() const {
	return luggageWeight;
}

void Ticket::addExpenses(double amount) {
	if (amount > 0.0) {
		paidAmount += amount;
	}
}

void Ticket::addBaggage(double weight) {
	if (weight > 0.0) {
		luggageWeight += weight;
		addExpenses(weight * 5.0);
	}
}