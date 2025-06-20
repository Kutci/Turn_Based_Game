#include "Commanders/Paladin.h"
#include "Armor/HeavyArmor.h"
Paladin::Paladin(const std::string &name) : Commander(name)
{
    this->health = 5000;
    this->maxHealth = 5000;
    this->mana = 3000;
    this->attack = 250;
    this->goldCost = 0;
    this->isCommander = true;
    this->armor = new HeavyArmor(20);
}

void Paladin::castSpell(std::vector<Unit *> &ownArmy,
                        std::vector<Unit *> &,
                        std::vector<Unit *> &graveyard,
                        const std::string &)
{
    for (Unit *ally : ownArmy)
    {
        if (ally->isAlive() && ally->isAliveUnit() && ally->getHealth() < ally->getMaxHealth())
        {
            if (mana >= 500)
            {
                unsigned prev = ally->getHealth();
                ally->setHealth(prev + 500);
                mana -= 500;
                /* std::cout << name << " heals " << ally->getTypeName()
                           << ". HP: " << prev << " -> " << ally->getHealth() << "\n";*/
                return;
            }
        }
    }

    for (size_t i = 0; i < graveyard.size(); ++i)
    {
        if (graveyard[i]->isAliveUnit())
        {
            if (mana >= 1000)
            {
                Unit *revived = graveyard[i]->clone();
                revived->setHealth(revived->getMaxHealth() / 2);
                ownArmy.push_back(revived);
                graveyard.erase(graveyard.begin() + i);
                mana -= 1000;
                // std::cout << name << " resurrects a fallen comrade.\n";
                return;
            }
        }
    }

    // std::cout << name << " found no ally to heal or resurrect.\n";
}

bool Paladin::isAliveUnit() const
{
    return true;
}

std::string Paladin::getTypeName() const
{
    return "Paladin";
}

void Paladin::print() const
{
    std::cout << "Paladin - " << name
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
Unit *Paladin::clone() const
{
    return new Paladin(*this);
}