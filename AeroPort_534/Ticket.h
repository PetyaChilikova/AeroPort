#pragma once
#include <string>

enum class TicketType {
	Standard,
	LastMinute,
	VIP
};

class Ticket {
protected:
	std::string ownerName;
	std::string flightId;
	double paidAmount;
	double luggageWeight;

public:
	Ticket(const std::string& owner, const std::string& flightId, double paidAmount, double luggage = 0.0);
	virtual ~Ticket() = default;

	std::string getOwnerName() const;
	std::string getFlightId() const;
	double getPaidAmount() const;
	double getLuggageWeight() const;

	void addExpenses(double amount);
	void addBaggage(double weight);

	virtual double getPassengerCancellationRefund() const = 0;
	virtual double getAdminCancellationRefund() const = 0;
	virtual TicketType getType() const = 0;
};
