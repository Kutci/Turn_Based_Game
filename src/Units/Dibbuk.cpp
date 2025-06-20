#include "Units/Dibbuk.h"

Dibbuk::Dibbuk() : Zombie()
{
    this->mana = 300;
}

void Dibbuk::print() const
{
    std::cout << "Dibbuk - HP: " << getHealth()
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

std::string Dibbuk::getTypeName() const
{
    return "Dibbuk";
}

Unit *Dibbuk::clone() const
{
    return new Dibbuk(*this);
}