#include "Admin.h"

Admin::Admin(const std::string& name, const std::string& password) : User(name, password, Role::Admin) {}

std::shared_ptr<Admin> Admin::getInstance() {
	static std::shared_ptr<Admin> instance(new Admin("admin", "admin"));
	return instance;	
}

void Admin::viewProfile() const {
	std::cout << "[Profile] User: " << name << " | Role: " << getRoleString() << " | Privilege: ALL_ACCESS\n";
}

void Admin::help() const {
	std::cout << "[System] Available commands for Administrator: " 
		<< "build-runway, build-hangar, close-runway, set-weather, register-airline, buy-aircraft, clone-aircraft, send-to-hangar, schedule-flight, retrieve-from-hangar, cancel-flight, flight-revenue, list-fleet, airport-report, audit-airline, view-profile, logout, save, load\n";
}