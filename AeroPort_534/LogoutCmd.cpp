#include "LogoutCmd.h"
#include "AirportManager.h"
#include <iostream>

void LogoutCmd::execute() {
    auto& manager = AirportManager::getInstance();

    if (manager.getCurrentUser() == nullptr) {
        std::cout << "[Error] No user is currently logged in.\n";
        return;
    }

    manager.getCurrentUser()->logout();

    manager.setCurrentUser(nullptr);
}

void LogoutCmd::undo() {
}