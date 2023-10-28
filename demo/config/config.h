//
// Created by loona on 27/10/23.
//

#pragma once

#include "nlohmann/json.hpp"
#include "fstream"

extern nlohmann::json config;

void loadConfig();