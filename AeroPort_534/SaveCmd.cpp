#include "SaveCmd.h"
#include "AirportManager.h"
#include <iostream>
#include <fstream>

SaveCmd::SaveCmd(std::stringstream& ss) {}

void SaveCmd::execute() {
    auto& manager = AirportManager::getInstance();

    std::ofstream out("aeroport_data.bin", std::ios::binary);
    if (!out) {
        std::cout << "[Error] Cannot open save file.\n";
        return;
    }

    auto allUsers = manager.getAllUsers(); 
    size_t userCnt = allUsers.size();
    out.write(reinterpret_cast<const char*>(&userCnt), sizeof(userCnt));

    for (const auto& u : allUsers) {
        u->serialize(out);
    }

    std::cout << "[System] AeroPort application state successfully serialized and saved to 'aeroport_data.bin'.\n";
}