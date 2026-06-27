#pragma once
#include "User.h"
#include "Ticket.h"
#include <vector>
#include <memory>

class Passenger : public User {
private:
	double balance;
	std::vector<std::shared_ptr<Ticket>> tickets;
public:
	Passenger(const std::string& name, const std::string& password, double initialBalance = 0.0);

	double getBalance() const;
	void addFunds(double amount);
	bool deductFunds(double amount);

	void addTicket(const std::shared_ptr<Ticket>& ticket);
	std::shared_ptr<Ticket> findTicket(const std::string& flightId) const;
	std::vector<std::shared_ptr<Ticket>> findAllTicketsForFlight(const std::string& flightId) const;
	void removeTicket(const std::shared_ptr<Ticket>& ticket);
	const std::vector<std::shared_ptr<Ticket>>& getTickets() const;

	void viewProfile() const override;
	void help() const override;

	void serialize(std::ofstream& out) const override;
	void deserialize(std::ifstream& in) override;
};
