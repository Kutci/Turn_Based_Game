#include "Armor/LeatherArmor.h"

LeatherArmor::LeatherArmor(unsigned durability) : Armor(durability) {}

unsigned LeatherArmor::reduceDamage(unsigned dmg)
{
    if (!canUse())
        return dmg;

    unsigned reduced = dmg - dmg / 4;
    use();
    return reduced;
}

Armor *LeatherArmor::clone() const
{
    return new LeatherArmor(*this);
}

const char *LeatherArmor::getTypeName() const { return "Leather Armor"; }