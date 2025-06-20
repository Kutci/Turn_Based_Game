#include "Units/Necromancer.h"
#include "Armor/Unarmored.h"

Necromancer::Necromancer() : Unit()
{
    this->health = 300;
    this->maxHealth = 300;
    this->mana = 200;
    this->attack = 4;
    this->goldCost = 400;
    this->isCommander = false;
    this->armor = new Unarmored(0);
}

void Necromancer::print() const
{
    std::cout << "Necromancer - HP: " << getHealth()
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

std::string Necromancer::getTypeName() const
{
    return "Necromancer";
}

Unit *Necromancer::clone() const
{
    return new Necromancer(*this);
}

bool Necromancer::isAliveUnit() const
{
    return false;
}

std::vector<Unit *> Necromancer::summon(const std::vector<Unit *> &deadAllies)
{
    std::vector<Unit *> summoned;

    if (mana < 150)
    {
        return summoned;
    }

    if (deadAllies.empty())
    {
        return summoned;
    }

    int count = 0;

    for (Unit *u : deadAllies)
    {

        if (!u->isAlive() && u->isAliveUnit())
        {
            summoned.push_back(new Skeleton());
            std::cout << "[Necromancer] Summoned Skeleton from " << u->getTypeName() << std::endl;
            count++;
            if (count == 3)
                break;
        }
    }

    if (!summoned.empty())
    {
        mana -= 150;
        std::cout << "[Necromancer] Mana after summoning: " << mana << std::endl;
    }
    else
    {
        std::cout << "[Necromancer] No units summoned." << std::endl;
    }

    return summoned;
}
