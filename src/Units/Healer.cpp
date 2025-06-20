#include "Units/Healer.h"
#include "Armor/Unarmored.h"
#include <iostream>

Healer::Healer() : Unit()
{
    this->health = 290;
    this->maxHealth = 290;
    this->mana = 200;
    this->attack = 2;
    this->goldCost = 150;
    this->armor = new Unarmored(0);
    this->isCommander = false;
}

void Healer::heal(Unit *target)
{
    if (!target || !isAlive())
        return;
    if (!target->isAlive())
        return;
    if (mana < 100)
    {
        std::cout << "Not enough mana to heal" << std::endl;
        return;
    }

    target->setHealth(target->getHealth() + 100);
    mana -= 100;
    std::cout << "Healer restored 100 health" << std::endl;
}
void Healer::print() const
{
    std::cout << "Healer - HP: " << getHealth()
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

Unit *Healer::clone() const
{
    return new Healer(*this);
}
std::string Healer::getTypeName() const
{
    return "Healer";
}

bool Healer::isAliveUnit() const
{
    return true;
}