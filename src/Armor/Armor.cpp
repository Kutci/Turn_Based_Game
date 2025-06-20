#include "Armor/Armor.h"

Armor::Armor(unsigned durability) : durability(durability) {}

bool Armor::canUse() const
{
    return durability > 0;
}

void Armor::use()
{
    if (durability > 0)
    {
        durability--;
    }
}

unsigned Armor::getDurability() const
{
    return durability;
}

void Armor::setDurability(unsigned durability)
{
    this->durability = durability;
}