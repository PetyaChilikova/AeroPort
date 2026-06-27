#pragma once
#include <string>
#include <iostream>

enum class Role {
	Passenger,
	Dispatcher,
	Admin
};

class User {
protected:
	std::string name;
	std::string password;
	Role role;

public:
	User(const std::string& name, const std::string& password, Role role);
	virtual ~User() = default;

	const std::string& getName() const;
	Role getRole() const;
	std::string getRoleString() const;

	bool checkPassword(const std::string& inputPassword) const;

	void logout();
	virtual void viewProfile() const = 0;
	virtual void help() const = 0;

	virtual void serialize(std::ofstream& out) const;
	virtual void deserialize(std::ifstream& in);
};