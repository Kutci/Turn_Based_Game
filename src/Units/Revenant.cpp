#include "Units/Revenant.h"

Revenant::Revenant() : Zombie()
{
    this->health = 600;
    this->maxHealth = 600;
}

void Revenant::print() const
{
    std::cout << "Revenant - HP: " << getHealth()
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

std::string Revenant::getTypeName() const
{
    return "Revenant";
}

Unit *Revenant::clone() const
{
    return new Revenant(*this);
}