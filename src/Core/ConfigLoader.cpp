#include "Core/ConfigLoader.h"
#include <fstream>
#include <sstream>

Config ConfigLoader::loadConfig(const std::string &fileName)
{
    Config config;
    std::ifstream file(fileName);
    std::string key;
    while (file >> key)
    {
        if (key == "STARTING_GOLD")
        {
            file >> config.startingGold;
        }
        else if (key == "UNIT_LIMIT")
        {
            file >> config.unitLimit;
        }
    }
    return config;
}

std::vector<std::string> ConfigLoader::loadCommanders(const std::string &fileName)
{
    std::vector<std::string> names;
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Cannot open commander names file\n";
        return names;
    }

    std::string name;
    while (std::getline(file, name))
    {
        if (!name.empty())
        {
            names.push_back(name);
        }
    }
    return names;
}
