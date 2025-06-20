#include "Core/Base.h"
#include "Core/UnitFactory.h"
#include <iostream>
#include <fstream>
Base::Base(unsigned gold, unsigned unitLimit) : gold(gold), unitLimit(unitLimit) {}

Base::~Base()
{
    for (Unit *u : units)
        delete u;
}

bool Base::canCreateUnit(unsigned cost) const
{
    return gold >= cost && units.size() < unitLimit;
}

bool Base::hasUnitLimit() const
{
    return units.size() < unitLimit;
}

bool Base::addUnit(Unit *unit)
{
    if (!canCreateUnit(unit->getGoldCost()))
    {
        return false;
    }

    gold -= unit->getGoldCost();
    units.push_back(unit);
    return true;
}

unsigned Base::getCommandersCount() const
{
    unsigned count = 0;
    for (Unit *u : units)
    {
        if (u->getIsCommander())
            count++;
    }
    return count;
}

void Base::printUnits() const
{
    for (const Unit *u : units)
    {
        if (u->getHealth() > 0)
            u->print();
    }
}
unsigned Base::getUnitCount() const
{
    return units.size();
}

unsigned Base::getGold() const
{
    return gold;
}

void Base::saveCommanders(std::ofstream &ofs) const
{
    unsigned count = 0;
    for (unsigned i = 0; i < units.size(); i++)
    {
        if (units[i]->getIsCommander() && units[i]->getHealth() > 0)
            count++;
    }

    ofs << count << std::endl;

    for (unsigned i = 0; i < units.size(); ++i)
    {
        if (units[i]->getIsCommander() && units[i]->getHealth() > 0)
        {
            ofs << units[i]->getName() << " " << units[i]->getTypeName() << " " << units[i]->getHealth() << " " << units[i]->getMana() << " " << units[i]->getArmorDurability() << std::endl;
        }
    }
}

void Base::loadCommanders(std::ifstream &ifs)
{
    unsigned count;
    ifs >> count;

    for (unsigned i = 0; i < count; i++)
    {
        std::string type, name;
        unsigned health, mana, durability;
        ifs >> name >> type >> health >> mana >> durability;

        Unit *unit = UnitFactory::createCommandersFromLine(type, name);

        if (unit)
        {
            unit->setHealth(health);
            unit->setMana(mana);
            unit->setDurability(durability);
            unit->setIsCommander(true);
            units.push_back(unit);
        }
    }
}

const std::vector<Unit *> &Base::getUnits() const
{
    return units;
}

std::vector<Unit *> Base::getCommanders() const
{
    std::vector<Unit *> commanders;
    for (Unit *u : units)
    {
        if (u->getIsCommander())
            commanders.push_back(u);
    }
    return commanders;
}

void Base::addGold(unsigned amount)
{
    gold += amount;
}