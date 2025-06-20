#include "Commanders/BladeDancer.h"
#include "Armor/MediumArmor.h"
BladeDancer::BladeDancer(const std::string &name) : Commander(name)
{
    this->health = 4000;
    this->maxHealth = 4000;
    this->attack = 300;
    this->mana = 0;
    this->goldCost = 0;
    this->isCommander = true;
    this->armor = new MediumArmor(25);
}
void BladeDancer::castSpell(std::vector<Unit *> &,
                            std::vector<Unit *> &,
                            std::vector<Unit *> &,
                            const std::string &)
{
    // std::cout << "BladeDancer has no magical abilities to cast.\n";
}
bool BladeDancer::isAliveUnit() const
{
    return true;
}

std::string BladeDancer::getTypeName() const
{
    return "BladeDancer";
}

void BladeDancer::print() const
{
    std::cout << "BladeDancer - " << name
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
Unit *BladeDancer::clone() const
{
    return new BladeDancer(*this);
}