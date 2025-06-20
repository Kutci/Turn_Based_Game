#pragma once
#include "Core/Commander.h"

class BladeDancer : public Commander
{
public:
    BladeDancer(const std::string &name);

    void castSpell(std::vector<Unit *> &ownArmy,
                   std::vector<Unit *> &enemyArmy,
                   std::vector<Unit *> &graveyard,
                   const std::string &extraInfo = "") override;
    void print() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;
    Unit *clone() const override;
};
