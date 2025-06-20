#include "Core/UnitFactory.h"
#include "Units/Healer.h"
#include "Units/Knight.h"
#include "Units/Infantry.h"
#include "Units/Archer.h"
#include "Units/Mage.h"
#include "Units/Necromancer.h"
#include "Units/Zombie.h"
#include "Units/Ghost.h"
#include "Units/Revenant.h"
#include "Units/Dibbuk.h"
#include "Units/Ghoul.h"
#include "Commanders/UndeadHunter.h"
#include "Commanders/DreadLord.h"
#include "Commanders/Lich.h"
#include "Commanders/BladeDancer.h"
#include "Commanders/Paladin.h"
#include "Units/Skeleton.h"
#include "Commanders/DeadKnight.h"
#include <sstream>
#include <fstream>

Unit *UnitFactory::createUnitFromLine(const std::string &line)
{
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if (type == "Healer")
    {
        return new Healer();
    }
    else if (type == "Necromancer")
    {
        return new Necromancer();
    }
    else if (type == "Infantry")
    {
        return new Infantry();
    }
    else if (type == "Archer")
    {
        return new Archer();
    }
    else if (type == "Knight")
    {
        return new Knight();
    }
    else if (type == "Mage")
    {
        return new Mage();
    }
    return nullptr;
}

Unit *UnitFactory::createCommandersFromLine(const std::string &type, const std::string &name)
{
    if (type == "Lich")
        return new Lich(name);
    else if (type == "DreadLord")
    {
        return new DreadLord(name);
    }
    else if (type == "DeadKnight")
    {
        return new DeadKnight(name);
    }
    else if (type == "UndeadHunter")
    {
        return new UndeadHunter(name);
    }
    else if (type == "BladeDancer")
    {
        return new BladeDancer(name);
    }

    else if (type == "Paladin")
    {
        return new Paladin(name);
    }

    return nullptr;
}

Unit *UnitFactory::createUndeadVersion(const Unit *deadUnit)
{
    if (!deadUnit->isAliveUnit())
        return nullptr;

    std::string type = deadUnit->getTypeName();

    if (type == "Knight")
    {
        if ((rand() % 100) < 25)
        {
            return new DeadKnight("DeadKnight");
        }
    }
    else
    {
        return new Skeleton();
    }

    return nullptr;
}

Unit *UnitFactory::createUndead()
{
    int choice = rand() % 7;

    switch (choice)
    {
    case 0:
        return new Skeleton();
    case 1:
        return new Ghoul();
    case 2:
        return new Zombie();
    case 3:
        return new Necromancer();
    case 4:
        return new Revenant();
    case 5:
        return new Ghost();
    case 6:
        return new Dibbuk();
    default:
        return new Skeleton();
    }
}

bool nameExists(const std::vector<std::string> &names, const std::string &name)
{
    for (size_t i = 0; i < names.size(); ++i)
    {
        if (names[i] == name)
        {
            return true;
        }
    }
    return false;
}

int countType(const std::vector<std::string> &types, const std::string &type)
{
    int count = 0;
    for (size_t i = 0; i < types.size(); ++i)
    {
        if (types[i] == type)
        {
            ++count;
        }
    }
    return count;
}

std::vector<Commander *> UnitFactory::loadCommanders(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs)
    {
        std::cerr << "Failed to open file\n";
        return std::vector<Commander *>();
    }

    std::vector<Commander *> commanders;
    std::vector<std::string> usedNames;
    std::vector<std::string> usedTypes;

    std::string type, name;
    while (ifs >> type >> name)
    {
        if (nameExists(usedNames, name))
        {
            std::cerr << "Duplicate name: " << name << "\n";
            continue;
        }

        int typeCount = countType(usedTypes, type);
        if (typeCount >= 7)
        {
            std::cerr << "Too many commanders of type " << type << "\n";
            continue;
        }

        Commander *commander = nullptr;
        if (type == "Lich")
        {
            commander = new Lich(name);
        }
        else if (type == "DreadLord")
        {
            commander = new DreadLord(name);
        }
        else if (type == "DeadKnight")
        {
            commander = new DeadKnight(name);
        }
        else if (type == "UndeadHunter")
        {
            commander = new UndeadHunter(name);
        }
        else if (type == "BladeDancer")
        {
            commander = new BladeDancer(name);
        }
        else if (type == "Paladin")
        {
            commander = new Paladin(name);
        }
        else
        {
            std::cerr << "Unknown type " << type << "\n";
            continue;
        }

        commanders.push_back(commander);
        usedNames.push_back(name);
        usedTypes.push_back(type);
    }

    return commanders;
}