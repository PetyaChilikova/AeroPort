#include "Aircraft.h"

Aircraft::Aircraft(int id, std::string model) : id(id), model(model), health(100.0) {}

bool Aircraft::requiresHeavyDuty() const {
	return false;
}

bool Aircraft::requiresVIPTerminal() const {
	return false;
}

std::string Aircraft::getModel() const {
	return model;
}

int Aircraft::getId() const {
	return id;
}

double Aircraft::getHealth() const {
	return health;
}

void Aircraft::repair() {
	health = 100.0;
}

bool Aircraft::canFly() const {
	return health >= 20.0;
}