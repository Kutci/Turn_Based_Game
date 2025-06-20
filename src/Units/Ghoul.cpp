#include "Units/Ghoul.h"
#include "Armor/HeavyArmor.h"

Ghoul::Ghoul() : Unit()
{
    this->health = 400;
    this->maxHealth = 400;
    this->attack = 12;
    this->goldCost = 250;
    this->isCommander = false;
    this->armor = new HeavyArmor(6);
}

void Ghoul::print() const
{
    std::cout << "Ghoul - HP: " << getHealth()
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

std::string Ghoul::getTypeName() const
{
    return "Ghoul";
}

Unit *Ghoul::clone() const
{
    return new Ghoul(*this);
}

bool Ghoul::isAliveUnit() const
{
    return false;
}