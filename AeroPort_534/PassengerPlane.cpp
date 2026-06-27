#include "PassengerPlane.h" 

PassengerPlane::PassengerPlane(int id, std::string model, int capacity) : Aircraft(id, model), passengerCapacity(capacity){}

double PassengerPlane::getMinRunwayLength() const {
	return 2000.0;
}

void PassengerPlane::processFlightEnd() {
	health *= 0.65;
	if (health < 0) {
		health = 0;
	}
}

double PassengerPlane::calculateAirportTax(double revenue) const {
	return revenue * 0.10;
}

std::shared_ptr<Aircraft> PassengerPlane::clone() const {
	return std::make_shared<PassengerPlane>(*this);
}

std::string PassengerPlane::getType() const {
	return "PassengerPlane";
}

int PassengerPlane::getCapacity() const {
	return passengerCapacity;
}

