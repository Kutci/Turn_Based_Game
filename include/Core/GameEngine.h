#pragma once
#include "Base.h"
#include "ConfigLoader.h"
#include <string>

class GameEngine
{
private:
    Base *base1;
    Base *base2;
    unsigned wonDuels[2] = {0, 0};
    std::string configPath;
    std::vector<Unit *> selectedCommanders;
    std::vector<Unit *> selectedAllies;

public:
    GameEngine();
    ~GameEngine();

    void selectBoss(const std::string &name);
    void selectUnits(const std::string &typeName, unsigned count);

    void saveGame(const std::string &fileName) const;
    void loadGame(const std::string &fileName);
    void restart();

    void init(const std::string &configFile);
    void startDuel();
    void run();
};
