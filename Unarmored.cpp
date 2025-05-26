#include "Unarmored.h"

Unarmored::Unarmored(unsigned durability) : Armor(durability) {}

unsigned Unarmored::reduceDamage(unsigned dmg)
{
    return dmg;
}

Armor *Unarmored::clone() const
{
    return new Unarmored(*this);
}

const char *Unarmored::getTypeName() const
{
    return "Unarmored";
}