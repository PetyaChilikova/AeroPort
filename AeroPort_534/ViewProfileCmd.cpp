#include "ViewProfileCmd.h"
#include "AirportManager.h"
#include <iostream>


void ViewProfileCmd::execute() {
    auto& manager = AirportManager::getInstance();
    auto currentUser = manager.getCurrentUser();

    if (!currentUser) {
        std::cout << "[Error] You must be logged in to view your profile!\n";
        return;
    }

    currentUser->viewProfile();
}

void ViewProfileCmd::undo() {
        
}