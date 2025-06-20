#pragma once

#include "Core/Commander.h"

class Paladin : public Commander
{
public:
    Paladin(const std::string &name);

    void castSpell(std::vector<Unit *> &ownArmy,
                   std::vector<Unit *> &,
                   std::vector<Unit *> &graveyard,
                   const std::string &) override;
    bool isAliveUnit() const override;
    std::string getTypeName() const override;
    void print() const override;
    Unit *clone() const override;
};