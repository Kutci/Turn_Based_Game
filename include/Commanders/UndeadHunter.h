#pragma once

#include "Core/Commander.h"

class UndeadHunter : public Commander
{
public:
    UndeadHunter(const std::string &name);

    void castSpell(std::vector<Unit *> &,
                   std::vector<Unit *> &enemyArmy,
                   std::vector<Unit *> &,
                   const std::string &) override;
    bool isAliveUnit() const override;
    std::string getTypeName() const override;
    void print() const override;
    Unit *clone() const override;
};