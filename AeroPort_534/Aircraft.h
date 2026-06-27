#pragma once
#include <string>
#include <memory>

class Aircraft {
protected:
	int id;
	std::string model;
	double health;
public:
	Aircraft(int id, std::string model);
	virtual ~Aircraft() = default;

	virtual double getMinRunwayLength() const = 0;
	virtual void processFlightEnd() = 0;
	virtual double calculateAirportTax(double revenue) const = 0;

	virtual std::shared_ptr<Aircraft> clone() const = 0;

	virtual bool requiresHeavyDuty() const;
	virtual bool requiresVIPTerminal() const;
	virtual std::string getType() const = 0;

	std::string getModel() const;
	int getId() const;
	double getHealth() const;
	void repair();
	bool canFly() const;
	void setId(int newId);
};
