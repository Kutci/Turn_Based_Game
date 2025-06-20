#pragma once

#include "Armor.h"

class Unarmored : public Armor
{
public:
    Unarmored(unsigned durability);
    unsigned reduceDamage(unsigned dmg);
    Armor *clone() const override;
    const char *getTypeName() const override;
};