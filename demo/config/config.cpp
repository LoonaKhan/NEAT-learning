//
// Created by loona on 27/10/23.
//

#include "config.h"

nlohmann::json config;

void loadConfig() {
    std::fstream f("../config/config.json");
    config = nlohmann::json::parse(f);
}