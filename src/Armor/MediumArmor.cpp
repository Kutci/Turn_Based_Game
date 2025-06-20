#include "Armor/MediumArmor.h"

MediumArmor::MediumArmor(unsigned durability) : Armor(durability) {}

unsigned MediumArmor::reduceDamage(unsigned dmg)
{
    if (!canUse())
        return dmg;

    unsigned reduced = dmg - dmg / 2;
    use();
    return reduced;
}

Armor *MediumArmor::clone() const
{
    return new MediumArmor(*this);
}

const char *MediumArmor::getTypeName() const
{
    return "Medium Armor";
}
