#include "Dispatcher.h"

Dispatcher::Dispatcher(const std::string& name, const std::string& password) : User(name, password, Role::Dispatcher) {}

void Dispatcher::viewProfile() const {
	std::cout << "[Profile] User: " << name << " | Role: " << getRoleString() << "\n";
}

void Dispatcher::help() const {
	std::cout << "[System] Available commands for Dispatcher: " 
		<< "list - airspace, list - runways, assign - runway, delay - flight, free - runway, undo, view - profile, logout\n";
}