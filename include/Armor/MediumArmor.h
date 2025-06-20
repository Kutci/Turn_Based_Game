#pragma once
#include "Armor.h"

class MediumArmor : public Armor
{
public:
    MediumArmor(unsigned durability);
    unsigned reduceDamage(unsigned dmg) override;
    Armor *clone() const override;

    const char *getTypeName() const override;
};