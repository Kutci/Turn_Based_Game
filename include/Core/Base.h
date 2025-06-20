#pragma once
#include <vector>
#include <string>
#include "../Core/Unit.h"

class Base
{
private:
    std::vector<Unit *> units;
    unsigned gold;
    unsigned unitLimit;

public:
    Base(unsigned gold, unsigned unitLimit);
    ~Base();

    bool canCreateUnit(unsigned cost) const;
    bool hasUnitLimit() const;
    bool addUnit(Unit *unit);
    void addGold(unsigned amount);
    const std::vector<Unit *> &getUnits() const;
    std::vector<Unit *> getCommanders() const;
    unsigned getCommandersCount() const;

    void saveCommanders(std::ofstream &ofs) const;
    void loadCommanders(std::ifstream &ifs);
    void printUnits() const;
    unsigned getUnitCount() const;
    unsigned getGold() const;
};
