#include "Units/Ghost.h"

Ghost::Ghost() : Unit()
{
    this->health = 0;
    this->maxHealth = 0;
    this->mana = 0;
    this->attack = 0;
    this->goldCost = 500;
    this->isCommander = false;
    this->armor = nullptr;
}

void Ghost::print() const
{
    std::cout << "Ghost - Ethereal unit (non-combat)"
              << ", Gold Cost: " << goldCost
              << std::endl;
}

std::string Ghost::getTypeName() const
{
    return "Ghost";
}

Unit *Ghost::clone() const
{
    return new Ghost(*this);
}

bool Ghost::isAliveUnit() const
{
    return false;
}

bool Ghost::sacrifice(Unit *target)
{
    if (!target && target->isAliveUnit())
        return false;

    target->setHealth(target->getHealth() + 250);

    this->health = 0;

    return true;
}