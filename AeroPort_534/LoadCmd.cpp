#include "LoadCmd.h"
#include "AirportManager.h"
#include "Passenger.h"
#include <iostream>
#include <fstream>

LoadCmd::LoadCmd(std::stringstream& ss) {}

void LoadCmd::execute() {
    auto& manager = AirportManager::getInstance();

    std::ifstream in("aeroport_data.bin", std::ios::binary);
    if (!in) {
        std::cout << "[System] No save file found. Starting a fresh instance of AeroPort System.\n";
        return;
    }

    manager.clearUsers();

    size_t userCnt;
    in.read(reinterpret_cast<char*>(&userCnt), sizeof(userCnt));

    for (size_t i = 0; i < userCnt; i++) {
        Role role;
        in.read(reinterpret_cast<char*>(&role), sizeof(role));

        if (role == Role::Passenger) {
            auto p = std::make_shared<Passenger>("", "", 0.0);
            p->deserialize(in);
            manager.addUser(p);
        }
    }

    std::cout << "[System] State loaded successfully from 'aeroport_data.bin'.\n";
}