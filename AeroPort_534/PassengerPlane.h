#pragma once
#include "Aircraft.h"

class PassengerPlane : public Aircraft {
private:
	int passengerCapacity;
public:
	PassengerPlane(int id, std::string model, int capacity);

	double getMinRunwayLength() const override;
	void processFlightEnd() override;
	double calculateAirportTax(double revenue) const override;
	std::shared_ptr<Aircraft> clone() const override;
	std::string getType() const override;
	int getCapacity() const;
 };
