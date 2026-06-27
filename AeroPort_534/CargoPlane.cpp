#include "CargoPlane.h"

CargoPlane::CargoPlane(int id, std::string model, int tonnage) : Aircraft(id, model), tonnage(tonnage) {}

double CargoPlane::getMinRunwayLength() const {
	return 3000.0;
}

void CargoPlane::processFlightEnd() {
	health *= 55.0;
	if (health < 0) {
		health = 0;
	}
}

double CargoPlane::calculateAirportTax(double revenue) const {
	return tonnage * 15.0;
}

std::shared_ptr<Aircraft> CargoPlane::clone() const {
	return std::make_shared<CargoPlane>(*this);
}

std::string CargoPlane::getType() const {
	return "CargoPlane";
}

bool CargoPlane::requiresHeavyDuty() const {
	return true;
}

int CargoPlane::getTonnage() const {
	return tonnage;
}