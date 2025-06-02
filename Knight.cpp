#include "Knight.h"
#include "HeavyArmor.h"
#include <iostream>

Knight::Knight() : Unit()
{
    this->health = 835;
    this->maxHealth = 835;
    this->attack = 45;
    this->mana = 0;
    this->goldCost = 700;
    this->armor = new HeavyArmor(10);
}

void Knight::print() const
{
    std::cout << "Knight - HP: " << getHealth()
              << ", ATK: " << getAttack()
              << ", Mana: " << getMana()
              << ", Commander: " << (getIsCommander() ? "Yes" : "No");

    if (armor)
    {
        std::cout << ", Armor: " << armor->getTypeName()
                  << " (Durability: " << armor->getDurability() << ")";
    }
    else
    {
        std::cout << ", Armor: None";
    }

    std::cout << std::endl;
}

Unit *Knight::clone() const
{
    return new Knight(*this);
}

Armor *Knight::getArmor() const
{
    return armor;
}

std::string Knight::getTypeName() const
{
    return "Knight";
}