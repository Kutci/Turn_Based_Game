#include "Commanders/Lich.h"
#include "Armor/HeavyArmor.h"
#include "Core/UnitFactory.h"
Lich::Lich(const std::string &name) : Commander(name)
{
    this->health = 1500;
    this->maxHealth = 1500;
    this->mana = 1000;
    this->attack = 100;
    this->goldCost = 0;
    this->isCommander = true;
    this->armor = new HeavyArmor(15);
}

void Lich::castSpell(std::vector<Unit *> &ownArmy,
                     std::vector<Unit *> &enemyArmy,
                     std::vector<Unit *> &graveyard,
                     const std::string &)
{
    if (mana >= 750 && !graveyard.empty())
    {
        mana -= 750;
        for (Unit *dead : graveyard)
        {
            Unit *raised = UnitFactory::createUndeadVersion(dead);
            if (raised)
            {
                ownArmy.push_back(raised);
                // std::cout << name << " raised undead from graveyard " << raised->getTypeName() << std::endl;
            }
        }
    }
    else
    {
        // std::cout << name << " cannot raise undead.\n";
    }
}
bool Lich::isAliveUnit() const
{
    return false;
}

std::string Lich::getTypeName() const
{
    return "Lich";
}

void Lich::print() const
{
    std::cout << "Lich - " << name
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

Unit *Lich::clone() const
{
    return new Lich(*this);
}