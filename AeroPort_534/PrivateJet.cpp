#include "PrivateJet.h"

PrivateJet::PrivateJet(int id, std::string model) : Aircraft(id, model) {}

double PrivateJet::getMinRunwayLength() const {
	return 1000.0;
}

void PrivateJet::processFlightEnd() {
	health *= 0.75;
}

double PrivateJet::calculateAirportTax(double revenue) const {
	return 5000.0;
}

std::shared_ptr<Aircraft> PrivateJet::clone() const {
	return std::make_shared<PrivateJet>(*this);
}

std::string PrivateJet::getType() const {
	return "PrivateJet";
}

bool PrivateJet::requiresVIPTerminal() const {
	return true;
}

