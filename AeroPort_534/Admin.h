#pragma once
#include "User.h"
#include <memory>

class Admin : public User {
private:
	Admin(const std::string& name, const std::string& password);
	Admin(const Admin&) = delete;
	Admin& operator=(const Admin&) = delete;

public:
	static std::shared_ptr<Admin> getInstance();
	void viewProfile() const override;
	void help() const override;
};