#pragma once
#include <string>
#include <vector>
#include "Commander.h"
struct Config
{
    unsigned startingGold = 0;
    unsigned unitLimit = 0;
};

class ConfigLoader
{
public:
    static Config loadConfig(const std::string &filename);
    static std::vector<std::string> loadCommanders(const std::string &filename);
};
