#pragma once
#include "Aircraft.h"

class CargoPlane : public Aircraft {
private:
	int tonnage;
public:
	CargoPlane(int id, std::string model, int tonnage);

	double getMinRunwayLength() const override;
	void processFlightEnd() override;
	double calculateAirportTax(double revenue) const override;
	std::shared_ptr<Aircraft> clone() const override;
	std::string CargoPlane::getType() const override;
	bool requiresHeavyDuty() const override;
	int getTonnage() const;
};
