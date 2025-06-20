#include "Armor/HeavyArmor.h"

HeavyArmor::HeavyArmor(unsigned durability) : Armor(durability) {}

unsigned HeavyArmor::reduceDamage(unsigned damage)
{
    if (!canUse())
        return damage;

    unsigned reduced = damage / 4;
    use();
    return reduced;
}

Armor *HeavyArmor::clone() const
{
    return new HeavyArmor(*this);
}

const char *HeavyArmor::getTypeName() const { return "Heavy Armor"; }