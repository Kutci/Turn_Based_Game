#pragma once
#include "Core/Commander.h"
class DeadKnight : public Commander
{
public:
    DeadKnight(const std::string &name);

    void castSpell(std::vector<Unit *> &ownArmy,
                   std::vector<Unit *> &,
                   std::vector<Unit *> &,
                   const std::string &) override;

    bool isAliveUnit() const override;
    std::string getTypeName() const override;
    void print() const override;
    Unit *clone() const override;
};