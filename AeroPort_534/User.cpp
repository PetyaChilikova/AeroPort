#include "User.h"
#include <fstream>

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

void User::serialize(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&role), sizeof(role));

    size_t nameLen = name.size();
    out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    out.write(name.data(), nameLen);

    size_t passLen = password.size();
    out.write(reinterpret_cast<const char*>(&passLen), sizeof(passLen));
    out.write(password.data(), passLen);
}

void User::deserialize(std::ifstream& in) {
    size_t nameLen;
    in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    name.resize(nameLen);
    in.read(&name[0], nameLen);

    size_t passLen;
    in.read(reinterpret_cast<char*>(&passLen), sizeof(passLen));
    password.resize(passLen);
    in.read(&passLen ? &password[0] : nullptr, passLen);
}