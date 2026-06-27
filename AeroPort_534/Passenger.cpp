#include "Passenger.h"
#include <algorithm>
#include <iomanip>

Passenger::Passenger (const std::string& name, const std::string& password, double initialBalance)
	: User(name, password, Role::Passenger), balance(initialBalance > 0.0 ? initialBalance : 0.0) {}

double Passenger::getBalance() const {
	return balance;
}

void Passenger::addFunds(double amount) {
	if (amount > 0.0) {
		balance += amount;
		auto oldFlags = std::cout.flags();
		std::cout << "[System] Funds added successfully. New balance: "
				<< std::fixed << std::setprecision(2) << balance << " EUR.\n";
		std::cout.flags(oldFlags);
	}
}

bool Passenger::deductFunds(double amount) {
	if (amount > 0.0 && balance >= amount) {
		balance -= amount;
		return true;
	}
	return false;
}

void Passenger::addTicket(const std::shared_ptr<Ticket>& ticket) {
	if (ticket) {
		tickets.push_back(ticket);
	}
}

std::shared_ptr<Ticket> Passenger::findTicket(const std::string& flightId) const {
	for (const auto& t : tickets) {
		if (t->getFlightId() == flightId) {
			return t;
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Ticket>> Passenger::findAllTicketsForFlight(const std::string& flightId) const {
	std::vector<std::shared_ptr<Ticket>> found;
	for (const auto& t : tickets) {
		if (t->getFlightId() == flightId) {
			found.push_back(t);
		}
	}
	return found;
}

void Passenger::removeTicket(const std::shared_ptr<Ticket>& ticket) {
	tickets.erase(std::remove(tickets.begin(), tickets.end(), ticket), tickets.end());
}

const std::vector<std::shared_ptr<Ticket>>& Passenger::getTickets() const {
	return tickets;
}

void Passenger::viewProfile() const {
	auto oldFlags = std::cout.flags();
	std::cout << "[Profile] User: " << name 
		<< " | Role: " << getRoleString() 
		<< " | Balance: " << std::fixed << std::setprecision(2) << balance << " EUR\n";
	std::cout.flags(oldFlags);
}

void Passenger::help() const {
	std::cout << "[System] Available commands for Passenger: \n"
		<< "add-funds – \"command description\"\n"
		<< "list-flights – \"command description\"\n"
		<< "filter-flights – \"command description\"\n"
		<< "book-ticket – \"command description\"\n"
		<< "upgrade-ticket – \"command description\"\n"
		<< "add-baggage – \"command description\"\n"
		<< "cancel-ticket – \"command description\"\n"
		<< "my-tickets – \"command description\"\n"
		<< "view-profile – \"command description\"\n"
		<< "logout – \"command description\"\n";
}