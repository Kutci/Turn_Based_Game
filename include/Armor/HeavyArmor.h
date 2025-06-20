#pragma once
#include "Armor.h"

class HeavyArmor : public Armor
{
public:
    HeavyArmor(unsigned durability);
    virtual unsigned reduceDamage(unsigned damage) override;
    Armor *clone() const override;

    const char *getTypeName() const override;
};