#pragma once
#include "Core/Unit.h"
#include "Skeleton.h"

class Necromancer : public Unit
{
public:
    Necromancer();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;
    std::vector<Unit *> summon(const std::vector<Unit *> &deadAllies) override;
};