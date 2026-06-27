#pragma once
#include "Aircraft.h"

class PrivateJet : public Aircraft {
private:
	static const int FIXED_CAPACITY = 12;
public:
	PrivateJet(int id, std::string model);

	double getMinRunwayLength() const override;
	void processFlightEnd() override;
	double calculateAirportTax(double revenue) const override;
	std::shared_ptr<Aircraft> clone() const override;
	std::string getType() const override;
	bool requiresVIPTerminal() const override;
};
