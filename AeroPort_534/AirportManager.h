#pragma once
#include <vector>
#include <memory>
#include <string>
#include <stack>
#include "User.h"
#include "Airline.h"
#include "Runway.h"
#include "Hangar.h"
#include "Flight.h"
#include "Aircraft.h"

class Command;

class AirportManager {
private:
	std::shared_ptr<User> currentUser;

	std::vector<std::shared_ptr<User>> allUsers;
	std::vector<std::shared_ptr<Airline>> allAirlines;
	std::vector<std::shared_ptr<Runway>> allRunways;
	std::vector<std::shared_ptr<Hangar>> allHangars;
	std::vector<std::shared_ptr<Flight>> allFlights;

	std::stack<std::shared_ptr<Command>> commandHistory;

	AirportManager();
	~AirportManager() = default;
	AirportManager(const AirportManager&) = delete;
	AirportManager& operator=(const AirportManager&) = delete;

public:
	static AirportManager& getInstance();

	void run();

	std::shared_ptr<User> getCurrentUser() const;
	void setCurrentUser(std::shared_ptr<User> user);

	void registerUser(std::shared_ptr<User> user);
	void registerAirline(std::shared_ptr<Airline> airline);
	void addRunway(std::shared_ptr<Runway> runway);
	void addHangar(std::shared_ptr<Hangar> hangar);
	void addFlight(std::shared_ptr<Flight> flight);

	std::shared_ptr<User> findUser(const std::string& username) const;
	std::shared_ptr<Airline> findAirline(const std::string& name) const;
	std::shared_ptr<Runway> findRunway(int id) const;
	std::shared_ptr<Hangar> findHangar(const std::string& id) const;
	std::shared_ptr<Flight> findFlight(const std::string& id) const;
	std::shared_ptr<Aircraft> findAircraftGlobal(int id) const;
	std::shared_ptr<Airline> findAirlineByAircraft(int aircraftId) const;

	const std::vector<std::shared_ptr<Flight>>& getAllFlights() const;
	const std::vector<std::shared_ptr<Runway>>& getAllRunways() const;

	void pushCommand(std::shared_ptr<Command> cmd);
	void popAndUndo();
};
