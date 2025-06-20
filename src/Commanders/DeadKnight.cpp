#include "Commanders/DeadKnight.h"
#include "Armor/HeavyArmor.h"
DeadKnight::DeadKnight(const std::string &name) : Commander(name)
{
    this->health = 2500;
    this->maxHealth = 2500;
    this->mana = 1000;
    this->attack = 150;
    this->goldCost = 0;
    this->isCommander = true;
    this->armor = new HeavyArmor(15);
}

void DeadKnight::castSpell(std::vector<Unit *> &ownArmy,
                           std::vector<Unit *> &,
                           std::vector<Unit *> &,
                           const std::string &)
{
    for (Unit *unit : ownArmy)
    {
        if (unit != this && !unit->isAliveUnit() && unit->isAlive())
        {
            if (mana >= 350)
            {
                unit->setHealth(unit->getHealth() + 350);
                mana -= 350;
                // std::cout << name << " healed undead unit.\n";
                return;
            }
        }
    }
    // std::cout << name << " cannot find undead to heal or not enough mana.\n";
}

bool DeadKnight::isAliveUnit() const
{
    return false;
}

std::string DeadKnight::getTypeName() const
{
    return "DeadKnight";
}

void DeadKnight::print() const
{
    std::cout << "DeadKnight - " << name
              << ", Health: " << getHealth()
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

Unit *DeadKnight::clone() const
{
    return new DeadKnight(*this);
}