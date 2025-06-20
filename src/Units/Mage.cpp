#include "Units/Mage.h"
#include "Armor/LeatherArmor.h"
#include <iostream>

Mage::Mage() : Unit()
{
    this->health = 325;
    this->maxHealth = 325;
    this->mana = 200;
    this->attack = 10;
    this->goldCost = 250;
    this->isCommander = false;
    this->armor = new LeatherArmor(3);
}

void Mage::attackEnemy(Unit *target)
{
    if (!target || !isAlive())
        return;
    if (mana < 50)
    {
        std::cout << "Mage doesn't have mana to cast attack" << std::endl;
        return;
    }

    target->takeDamage(attack);
    mana -= 50;
}

void Mage::print() const
{
    std::cout << "Mage - HP: " << getHealth()
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

Unit *Mage::clone() const
{

    return new Mage(*this);
}

std::string Mage::getTypeName() const
{
    return "Mage";
}

bool Mage::isAliveUnit() const
{
    return true;
}