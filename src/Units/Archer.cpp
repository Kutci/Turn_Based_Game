#include "Units/Archer.h"
#include "Armor/MediumArmor.h"
#include <iostream>
Archer::Archer() : Unit()
{
    this->health = 535;
    this->maxHealth = 535;
    this->attack = 10;
    this->mana = 0;
    this->goldCost = 300;
    this->isCommander = false;
    this->armor = new MediumArmor(3);
}

void Archer::print() const
{
    std::cout << "Archer - HP: " << getHealth()
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

Unit *Archer::clone() const
{
    return new Archer(*this);
}
std::string Archer::getTypeName() const
{
    return "Archer";
}

bool Archer::isAliveUnit() const
{
    return true;
}