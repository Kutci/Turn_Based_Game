#pragma once
#include <string>

#include "Core/Unit.h"

class Mage : public Unit
{
public:
    Mage();

    void attackEnemy(Unit *target) override;
    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;
};