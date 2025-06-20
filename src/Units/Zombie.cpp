#include "Units/Zombie.h"
#include "Armor/Unarmored.h"

Zombie::Zombie() : Unit()
{
    this->health = 250;
    this->maxHealth = 250;
    this->attack = 15;
    this->mana = 0;
    this->goldCost = 300;
    this->isCommander = false;
    this->armor = new Unarmored(0);
}

void Zombie::print() const
{
    std::cout << "Zombie - HP: " << getHealth()
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

std::string Zombie::getTypeName() const
{
    return "Zombie";
}

Unit *Zombie::clone() const
{
    return new Zombie(*this);
}

bool Zombie::isAliveUnit() const
{
    return false;
}