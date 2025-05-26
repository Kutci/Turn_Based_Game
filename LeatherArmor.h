#pragma once

#include "Armor.h"

class LeatherArmor : public Armor
{
public:
    LeatherArmor(unsigned durability);
    unsigned reduceDamage(unsigned dmg) override;
    Armor *clone() const override;

    const char *getTypeName() const override;
};