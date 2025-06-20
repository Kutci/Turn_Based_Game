#include "Units/Skeleton.h"
#include "Armor/MediumArmor.h"

Skeleton::Skeleton() : Unit()
{
    this->health = 500;
    this->maxHealth = 500;
    this->attack = 5;
    this->mana = 0;
    this->goldCost = 100;
    this->isCommander = false;
    this->armor = new MediumArmor(8);
}

void Skeleton::print() const
{
    std::cout << "Skeleton - HP: " << getHealth()
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

std::string Skeleton::getTypeName() const
{
    return "Skeleton";
}

Unit *Skeleton::clone() const
{
    return new Skeleton(*this);
}

bool Skeleton::isAliveUnit() const
{
    return false;
}