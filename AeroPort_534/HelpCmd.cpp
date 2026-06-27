#include "HelpCmd.h"
#include "AirportManager.h"
#include <iostream>

void HelpCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser) {
        std::cout << "[System] Guest Menu. Available commands: login, register, exit\n";
        return;
    }

    currentUser->help();
}

void HelpCmd::undo() {
}