#include "Commanders/UndeadHunter.h"
#include "Armor/HeavyArmor.h"
UndeadHunter::UndeadHunter(const std::string &name) : Commander(name)
{
    this->health = 2000;
    this->maxHealth = 2000;
    this->mana = 1500;
    this->attack = 75;
    this->goldCost = 0;
    this->isCommander = true;
    this->armor = new HeavyArmor(17);
}

void UndeadHunter::castSpell(std::vector<Unit *> &,
                             std::vector<Unit *> &enemyArmy,
                             std::vector<Unit *> &,
                             const std::string &)
{
    for (Unit *target : enemyArmy)
    {
        if (!target->isAlive())
            continue;
        if (!target->isAliveUnit() && target->getIsCommander())
        {
            if (mana >= 1000)
            {
                target->takeDamage(target->getHealth() + 9999);
                mana -= 1000;
                // std::cout << name << " destroyed undead commander " << target->getName() << ".\n";
                return;
            }
            else
            {
                // std::cout << name << " lacks mana to execute the undead commander.\n";
                return;
            }
        }
    }

    // std::cout << name << " found no undead commander to destroy.\n";
}

bool UndeadHunter::isAliveUnit() const
{
    return true;
}

std::string UndeadHunter::getTypeName() const
{
    return "UndeadHunter";
}

void UndeadHunter::print() const
{
    std::cout << "UndeadHunter - " << name
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

Unit *UndeadHunter::clone() const
{
    return new UndeadHunter(*this);
}