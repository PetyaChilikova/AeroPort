#pragma once
#include "User.h"

class Dispatcher : public User {
public: 
	Dispatcher(const std::string& name, const std::string& password);
	void viewProfile() const override;
	void help() const override;
};
