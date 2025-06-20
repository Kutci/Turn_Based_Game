#pragma once
#include "Unit.h"
#include <string>
class Commander;

class UnitFactory
{
public:
    static Unit *createUnitFromLine(const std::string &line);
    static Unit *createCommandersFromLine(const std::string &type, const std::string &name);

    static Unit *createUndead();
    static Unit *createUndeadVersion(const Unit *deadUnit);
    static std::vector<Commander *> loadCommanders(const std::string &filename);
};
