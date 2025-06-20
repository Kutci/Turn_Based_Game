#include "Commanders/DreadLord.h"
#include "Armor/HeavyArmor.h"
#include "Units/Necromancer.h"
#include "Units/Ghoul.h"
DreadLord::DreadLord(const std::string &name) : Commander(name), summonCount(0)
{
    this->health = 3000;
    this->maxHealth = 3000;
    this->mana = 2000;
    this->attack = 200;
    this->goldCost = 0;
    this->isCommander = true;
    this->armor = new HeavyArmor(20);
}

void DreadLord::castSpell(std::vector<Unit *> &ownArmy,
                          std::vector<Unit *> &,
                          std::vector<Unit *> &,
                          const std::string &summonType)
{

    if (summonCount < 2)
    {

        if (summonType == "NECROMANCER" && mana >= 400)
        {
            ownArmy.push_back(new Necromancer());
            mana -= 400;
            // std::cout << name << " summons Necromancer!\n";
            summonCount++;
        }
        else if (summonType == "GHOUL" && mana >= 500)
        {
            ownArmy.push_back(new Ghoul());
            mana -= 500;
            // std::cout << name << " summons Ghoul!\n";
            summonCount++;
        }
        else
        {
            // std::cout << name << " cannot summon " << summonType << ".\n";
        }
    }
}

bool DreadLord::isAliveUnit() const
{
    return false;
}

std::string DreadLord::getTypeName() const
{
    return "DreadLord";
}

void DreadLord::print() const
{
    std::cout << "DreadLord - " << name
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

Unit *DreadLord::clone() const
{
    return new DreadLord(*this);
}