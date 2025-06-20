#include "Units/Infantry.h"
#include "Armor/MediumArmor.h"
#include <iostream>
Infantry::Infantry() : Unit()
{
    this->health = 420;
    this->maxHealth = 420;
    this->attack = 7;
    this->goldCost = 250;
    this->mana = 0;
    this->isCommander = false;
    this->armor = new MediumArmor(8);
}

void Infantry::print() const
{
    std::cout << "Infantry - HP: " << getHealth()
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

Unit *Infantry::clone() const
{
    return new Infantry(*this);
}

std::string Infantry::getTypeName() const
{
    return "Infantry";
}

bool Infantry::isAliveUnit() const
{
    return true;
}