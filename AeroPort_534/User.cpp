#include "User.h"

User::User(const std::string& name, const std::string& password, Role role) : name(name), password(password), role(role) {}

const std::string& User::getName() const {
	return name;
}

Role User::getRole() const {
	return role;
}

std::string User::getRoleString() const {
	switch (role) {
	case Role::Passenger:
		return "Passenger";
	case Role::Dispatcher:
		return "Dispatcher";
	case Role::Admin:
		return "System Administrator";
	default:
		return "Unknown";
	}
}

bool User::checkPassword(const std::string& inputPassword) const{
	return password == inputPassword;
}

void User::logout() {
	std::cout << "[System] Logged out successfully." << std::endl;
}
