#include "Core/Unit.h"
#include <stdexcept>
Unit::Unit()
    : armor(nullptr), health(0), maxHealth(0), attack(0), goldCost(0), mana(0), isCommander(false)
{
}
void Unit::copyFrom(const Unit &other)
{
    Armor *newArmor = other.armor ? other.armor->clone() : nullptr;
    delete armor;
    armor = newArmor;

    health = other.health;
    attack = other.attack;
    goldCost = other.goldCost;
    mana = other.mana;
    isCommander = other.isCommander;
}

Unit::Unit(const Unit &other)
{
    copyFrom(other);
}

Unit &Unit::operator=(const Unit &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }

    return *this;
}

unsigned Unit::getAttack() const
{
    return attack;
}

unsigned Unit::getMana() const
{

    return mana;
}

unsigned Unit::getHealth() const
{

    return health;
}

unsigned Unit::getGoldCost() const
{
    return goldCost;
}

bool Unit::getIsCommander() const
{
    return isCommander;
}
bool Unit::isAlive() const
{
    return health > 0;
}

std::string Unit::getName() const
{
    return "";
}
unsigned Unit::getMaxHealth() const
{
    return maxHealth;
}

unsigned Unit::getArmorDurability() const
{
    return armor ? armor->getDurability() : 0;
}
void Unit::setHealth(unsigned health)
{
    this->health = health > maxHealth ? maxHealth : health;
}

void Unit::setMana(unsigned mana)
{
    this->mana = mana;
}

void Unit::setDurability(unsigned durability)
{
    if (armor)
        armor->setDurability(durability);
}

void Unit::addMana(unsigned amount)
{
    this->mana += amount;
}

void Unit::setIsCommander(bool val)
{
    isCommander = val;
}

void Unit::free()
{
    delete armor;
    armor = nullptr;
}

Unit::~Unit()
{
    free();
}

void Unit::takeDamage(unsigned dmg)
{
    if (armor)
        dmg = armor->reduceDamage(dmg);
    if (dmg >= health)
        health = 0;
    else
        health -= dmg;
}

void Unit::attackEnemy(Unit *target)
{
    if (target && isAlive())
        target->takeDamage(attack);
}

bool Unit::sacrifice(Unit *target)
{
    return false;
}

void Unit::heal(Unit *target)
{
}

std::vector<Unit *> Unit::summon(const std::vector<Unit *> &deadAllies)
{
    return {};
}