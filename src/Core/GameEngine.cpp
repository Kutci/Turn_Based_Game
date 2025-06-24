#include "Core/GameEngine.h"
#include "Core/UnitFactory.h"
#include <iostream>
#include <fstream>
GameEngine::GameEngine() : base1(nullptr), base2(nullptr) {}

GameEngine::~GameEngine()
{
    delete base1;
    delete base2;
}

void GameEngine::init(const std::string &configFile)
{
    configPath = configFile;
    Config cfg = ConfigLoader::loadConfig(configFile);
    base1 = new Base(cfg.startingGold, cfg.unitLimit);
    base2 = new Base(cfg.startingGold, cfg.unitLimit);

    std::vector<Commander *> commanders = UnitFactory::loadCommanders("assets/commanders.cfg");

    const int maxCommanders = 7;

    for (Commander *commander : commanders)
    {
        if (commander->isAliveUnit())
        {
            if (base1->getCommandersCount() < maxCommanders)
            {
                if (!base1->addUnit(commander))
                {
                    std::cerr << "Failed to add living commander " << commander->getTypeName() << " to base1" << std::endl;
                    delete commander;
                }
            }
            else
            {
                delete commander;
            }
        }
        else
        {
            if (base2->getCommandersCount() < maxCommanders)
            {
                if (!base2->addUnit(commander))
                {
                    std::cerr << "Failed to add undead commander " << commander->getTypeName() << " to base2" << std::endl;
                    delete commander;
                }
            }
            else
            {
                delete commander;
            }
        }
    }
}

std::string toUpper(const std::string &s)
{
    std::string result = s;
    for (size_t i = 0; i < result.size(); ++i)
    {
        if (result[i] >= 'a' && result[i] <= 'z')
            result[i] = result[i] - 'a' + 'A';
    }
    return result;
}

bool stringToInt(const std::string &str, int &result)
{
    result = 0;
    if (str.empty())
        return false;

    size_t i = 0;
    bool isNegative = false;

    if (str[0] == '-')
    {
        isNegative = true;
        i = 1;
        if (str.size() == 1)
            return false;
    }

    for (; i < str.size(); ++i)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return false;
        }
        result = result * 10 + (str[i] - '0');
    }

    if (isNegative)
        result = -result;

    return true;
}

void GameEngine::run()
{
    std::string cmd;
    int side;

    std::cout << "Commands: CREATE <side 1> <unit_type>" << std::endl;
    std::cout << "          SELECT BOSS <name>" << std::endl;
    std::cout << "          SELECT <count> <unit_type>" << std::endl;
    std::cout << "          DUEL" << std::endl;
    std::cout << "          PRINT <side>" << std::endl;
    std::cout << "          SAVE <filename>" << std::endl;
    std::cout << "          LOAD <filename>" << std::endl;
    std::cout << "          RESTART" << std::endl;
    std::cout << "          EXIT" << std::endl;

    while (std::cin >> cmd)
    {

        std::string cmdUpper = toUpper(cmd);
        if (cmdUpper == "CREATE")
        {
            std::string unitType;
            std::cin >> side >> unitType;

            if (side == 2)
            {
                std::cout << "You can create units only in team 1." << std::endl;
                continue;
            }
            else if (side != 1)
            {
                continue;
            }
            Unit *u = UnitFactory::createUnitFromLine(unitType);
            if (!u)
            {
                std::cout << "Invalid unit type." << std::endl;
                continue;
            }

            Base *b = base1;
            if (!b->addUnit(u))
            {
                std::cout << "Not enough gold or unit limit reached." << std::endl;
            }
            else
            {
                std::cout << "Unit created!" << std::endl;
                std::cout << "BASE 1 Remaining gold : " << b->getGold() << std::endl;
            }
        }
        else if (cmdUpper == "SELECT")
        {
            std::string subcmd;
            std::cin >> subcmd;

            std::string subcmdUpper = toUpper(subcmd);

            if (subcmdUpper == "BOSS")
            {
                std::string name;
                std::cin >> name;
                selectBoss(name);
            }
            else
            {
                int times = 0;
                if (!stringToInt(subcmd, times))
                {
                    std::cout << "Invalid count for SELECT command." << std::endl;
                    continue;
                }

                std::string unitName;
                std::cin >> unitName;

                selectUnits(unitName, times);
            }
        }

        else if (cmdUpper == "DUEL")
        {
            if (selectedCommanders.empty())
            {
                std::cout << "You must select a commander first with SELECT BOSS <name>." << std::endl;
                continue;
            }

            if (selectedAllies.empty())
            {
                std::cout << "You must select at least one unit with SELECT <count> <unit_type>." << std::endl;
                continue;
            }

            startDuel();
        }
        else if (cmdUpper == "PRINT")
        {
            std::cin >> side;
            Base *b = (side == 1 ? base1 : base2);
            b->printUnits();
        }
        else if (cmdUpper == "SAVE")
        {
            std::string filename;
            std::cin >> filename;
            saveGame(filename);
        }
        else if (cmdUpper == "LOAD")
        {
            std::string filename;
            std::cin >> filename;
            loadGame(filename);
        }
        else if (cmdUpper == "RESTART")
        {
            restart();
        }
        else if (cmdUpper == "EXIT")
        {
            std::string choice;
            std::cout << "Do you want to save before exiting? (yes/no): ";
            std::cin >> choice;
            if (choice == "yes")
            {
                std::string filename;
                std::cout << "Enter filename to save: ";
                std::cin >> filename;
                saveGame(filename);
            }
            break;
        }
        else
        {
            std::cout << "Unknown command." << std::endl;
        }
    }
}

void undeadTurn(std::vector<Unit *> &undeadArmy,
                std::vector<Unit *> &livingAttackers,
                std::vector<Unit *> &undeadGraveyard,
                std::vector<Unit *> &selectedAllies, Base *base2)
{
    // std::cout << "Undead attack!" << std::endl;
    for (Unit *undead : undeadArmy)
    {
        if (!undead->isAlive())
            continue;

        /* std::cout << "Undead attacker: ";
         undead->print();*/

        if (undead->getIsCommander())
        {
            std::string summonType;

            if (undead->getTypeName() == "DreadLord" && base2 && base2->hasUnitLimit())
            {
                summonType = (rand() % 2 == 0) ? "NECROMANCER" : "GHOUL";
            }

            dynamic_cast<Commander *>(undead)->castSpell(undeadArmy, selectedAllies, undeadGraveyard, summonType);
        }
        for (Unit *ally : livingAttackers)
        {
            if (!ally->isAlive())
                continue;

            if (undead->getTypeName() == "Ghost")
            {
                Unit *toSacrifice = nullptr;
                for (Unit *u : undeadArmy)
                {
                    if (u != undead && u->isAlive())
                    {
                        toSacrifice = u;
                        break;
                    }
                }
                undead->sacrifice(toSacrifice ? toSacrifice : undead);
            }
            else if (undead->getTypeName() == "Necromancer")
            {
                std::vector<Unit *> newSkeletons = undead->summon(undeadGraveyard);
                for (Unit *s : newSkeletons)
                {
                    undeadArmy.push_back(s);
                    // std::cout << "Necromancer summoned a Skeleton!" << std::endl;
                }
            }

            // std::cout << undead->getTypeName() << " attacks " << ally->getTypeName() << "!" << std::endl;
            int hpBefore = ally->getHealth();
            undead->attackEnemy(ally);
            int damage = hpBefore - ally->getHealth();

            // std::cout << ally->getTypeName() << " took " << damage << " damage. HP: " << hpBefore << " -> " << ally->getHealth() << std::endl;
            break;
        }

        undead->addMana(75);
    }
}

void livingTurn(std::vector<Unit *> &livingAttackers,
                std::vector<Unit *> &undeadArmy,
                std::vector<Unit *> &livingGraveyard,
                std::vector<Unit *> &undeadGraveyard,
                const std::vector<Unit *> &selectedAllies,
                const std::vector<Unit *> &selectedCommanders)
{

    // std::cout << "Living attack!" << std::endl;
    for (Unit *ally : livingAttackers)
    {
        if (!ally->isAlive())
            continue;

        /*std::cout << "Living attacker: ";
        ally->print();*/

        if (ally->getIsCommander())
        {
            // std::cout << ally->getTypeName() << " is casting a spell..." << std::endl;
            if (ally->getTypeName() == "Paladin")
            {
                dynamic_cast<Commander *>(ally)->castSpell(livingAttackers, undeadArmy, livingGraveyard);
            }
            else
            {
                dynamic_cast<Commander *>(ally)->castSpell(livingAttackers, undeadArmy, undeadGraveyard);
            }
        }

        for (Unit *undead : undeadArmy)
        {
            if (!undead->isAlive())
                continue;

            if (ally->getTypeName() == "Healer")
            {
                for (Unit *friendUnit : livingAttackers)
                {
                    if (friendUnit->isAlive() && friendUnit->getHealth() < friendUnit->getMaxHealth())
                    {
                        ally->heal(friendUnit);
                        // std::cout << "Healer healed " << friendUnit->getTypeName() << std::endl;
                        break;
                    }
                }
            }

            // std::cout << ally->getTypeName() << " attacks " << undead->getTypeName() << "!" << std::endl;
            int hpBefore = undead->getHealth();
            ally->attackEnemy(undead);
            int damage = hpBefore - undead->getHealth();

            // std::cout << undead->getTypeName() << " took " << damage << " damage. HP: " << hpBefore << " -> " << undead->getHealth() << std::endl;
            break;
        }

        ally->addMana(75);
    }
}

void GameEngine::startDuel()
{
    std::cout << std::endl;

    std::vector<Unit *> livingGraveyard;
    std::vector<Unit *> undeadGraveyard;
    std::vector<Unit *> undeadArmy;

    std::vector<Unit *> livingAttackers = selectedAllies;
    livingAttackers.insert(livingAttackers.end(), selectedCommanders.begin(), selectedCommanders.end());

    std::cout << "Base 1 selected commander(s) for duel:" << std::endl;
    if (!selectedCommanders.empty())
    {
        for (Unit *commander : selectedCommanders)
            commander->print();
    }
    else
    {
        std::cout << "No commanders selected." << std::endl;
        return;
    }

    std::cout << "Base 1 selected non-commander allies for duel:" << std::endl;
    for (Unit *unit : selectedAllies)
    {
        if (!unit->getIsCommander())
            unit->print();
    }
    std::cout << std::endl;

    std::vector<Unit *> allUndeadCommanders = base2->getCommanders();
    std::cout << "Base2 commanders count: " << allUndeadCommanders.size() << std::endl;
    if (allUndeadCommanders.empty())
    {
        std::cout << "No undead commanders available." << std::endl;
        return;
    }

    std::cout << "Log" << std::endl;
    for (size_t i = allUndeadCommanders.size() - 1; i > 0; --i)
    {
        size_t j = rand() % (i + 1);
        std::swap(allUndeadCommanders[i], allUndeadCommanders[j]);
    }

    int commanderCount = 1 + rand() % allUndeadCommanders.size();
    for (int i = 0; i < commanderCount; ++i)
    {
        if (allUndeadCommanders[i]->isAlive())
            undeadArmy.push_back(allUndeadCommanders[i]);
    }

    int unitCount = rand() % 5 + 1;

    for (int i = 0; i < unitCount; ++i)
    {
        Unit *u = UnitFactory::createUndead();
        if (!u)
        {
            continue;
        }

        undeadArmy.push_back(u);
    }

    std::cout << "Base 2 units and commanders for duel:" << std::endl;
    for (Unit *unit : undeadArmy)
        unit->print();
    std::cout << std::endl;

    std::vector<Unit *> newLivingDead;
    std::vector<Unit *> newUndeadDead;
    while (true)
    {
        undeadTurn(undeadArmy, livingAttackers, undeadGraveyard, selectedAllies, base2);

        for (int i = 0; i < (int)selectedAllies.size();)
        {
            if (!selectedAllies[i]->isAlive())
            {
                Unit *deadUnit = selectedAllies[i];
                livingGraveyard.push_back(deadUnit);

                Unit *undeadUnit = UnitFactory::createUndeadVersion(deadUnit);
                if (undeadUnit)
                {
                    undeadArmy.push_back(undeadUnit);
                    // std::cout << "A DeadKnight has risen from the fallen Knight!" << std::endl;
                }

                selectedAllies.erase(selectedAllies.begin() + i);
            }
            else
            {
                ++i;
            }
        }

        livingTurn(livingAttackers, undeadArmy, livingGraveyard, undeadGraveyard, selectedAllies, selectedCommanders);

        for (int i = 0; i < (int)undeadArmy.size();)
        {
            if (!undeadArmy[i]->isAlive())
            {
                undeadGraveyard.push_back(undeadArmy[i]);
                undeadArmy.erase(undeadArmy.begin() + i);
            }
            else
            {
                ++i;
            }
        }

        bool undeadAlive = false;
        for (Unit *u : undeadArmy)
            if (u->isAlive())
                undeadAlive = true;

        bool livingAlive = false;
        for (Unit *u : livingAttackers)
            if (u->isAlive())
                livingAlive = true;

        if (!undeadAlive || !livingAlive)
            break;

        livingGraveyard = newLivingDead;
        undeadGraveyard = newUndeadDead;

        newLivingDead.clear();
        newUndeadDead.clear();
    }

    std::cout << "\nLiving army units and commanders AFTER duel:" << std::endl;
    for (Unit *unit : selectedAllies)
        unit->print();

    std::cout << "\nUndead army units and commanders AFTER duel:" << std::endl;
    for (Unit *unit : undeadArmy)
        unit->print();

    bool undeadAlive = false;
    for (Unit *u : undeadArmy)
        if (u->isAlive())
            undeadAlive = true;

    bool livingAlive = false;
    for (Unit *u : livingAttackers)
        if (u->isAlive())
            livingAlive = true;

    std::cout << std::endl;
    if (livingAlive && !undeadAlive)
    {
        std::cout << "The living have won the duel!" << std::endl;
        wonDuels[0]++;
        std::cout << "Base 1 wonduels: " << wonDuels[0] << std::endl;

        if (wonDuels[0] >= 3)
        {
            std::cout << "\nBase 1 has won 3 duels! Game Over.\n";
            exit(0);
        }
    }
    else if (!livingAlive && undeadAlive)
    {
        std::cout << "The undead have won the duel!" << std::endl;
        wonDuels[1]++;
        std::cout << "Base 2 wonduels: " << wonDuels[1] << std::endl;

        if (wonDuels[1] >= 3)
        {
            std::cout << "\nBase 2 has won 3 duels! Game Over.\n";
            exit(0);
        }
    }
    else
    {
        std::cout << "The duel ended in total annihilation!" << std::endl;
    }

    base1->addGold(1000);
    base2->addGold(1000);

    selectedAllies.clear();
    selectedCommanders.clear();
}

void GameEngine::selectBoss(const std::string &name)
{
    const std::vector<Unit *> &units = base1->getUnits();

    for (Unit *unit : units)
    {
        if (unit->getName() == name && unit->getIsCommander() && unit->isAlive())
        {
            for (Unit *cmd : selectedCommanders)
            {
                if (cmd == unit)
                {
                    std::cout << "Commander " << name << " already selected." << std::endl;
                    return;
                }
            }

            selectedCommanders.push_back(unit);
            std::cout << "Selected commander: " << name << "" << std::endl;
            return;
        }
    }

    std::cout << "Commander " << name << " not found in base 1." << std::endl;
}

bool isAlreadySelected(Unit *unit, const std::vector<Unit *> &selected)
{
    for (size_t i = 0; i < selected.size(); ++i)
    {
        if (selected[i] == unit)
            return true;
    }
    return false;
}

void GameEngine::selectUnits(const std::string &typeName, unsigned count)
{
    const std::vector<Unit *> &units = base1->getUnits();

    unsigned selectedCount = 0;

    for (Unit *unit : units)
    {
        if (unit->getTypeName() == typeName && !unit->getIsCommander() && unit->isAlive())
        {
            if (!isAlreadySelected(unit, selectedAllies))
            {
                selectedAllies.push_back(unit);
                selectedCount++;

                if (selectedCount == count)
                    break;
            }
        }
    }

    if (selectedCount == 0)
    {
        std::cout << "No units of type \"" << typeName << "\" found in base 1 or all already selected." << std::endl;
    }
    else
    {
        std::cout << "Selected " << selectedCount << " unit(s) of type " << typeName << "." << std::endl;
    }
}

void GameEngine::saveGame(const std::string &filename) const
{
    std::ofstream ofs(filename);
    if (!ofs)
    {
        std::cerr << "Failed to open save file." << std::endl;
        return;
    }

    ofs << base1->getGold() << " " << base2->getGold() << "" << std::endl;
    ofs << wonDuels[0] << " " << wonDuels[1] << "" << std::endl;

    base1->saveCommanders(ofs);
    base2->saveCommanders(ofs);
}

void GameEngine::loadGame(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs)
    {
        std::cerr << "Failed to open save file." << std::endl;
        return;
    }

    unsigned gold1, gold2;
    ifs >> gold1 >> gold2;
    ifs >> wonDuels[0] >> wonDuels[1];

    delete base1;
    delete base2;
    Config cfg = ConfigLoader::loadConfig(configPath);
    base1 = new Base(gold1, cfg.unitLimit);
    base2 = new Base(gold2, cfg.unitLimit);

    std::cout << "Game loaded from " << filename << "" << std::endl;
    std::cout << "Base1 gold: " << gold1 << "Base2 gold: " << gold2 << std::endl;

    base1->loadCommanders(ifs);
    base2->loadCommanders(ifs);
}

void GameEngine::restart()
{
    delete base1;
    delete base2;

    wonDuels[0] = wonDuels[1] = 0;

    init(configPath);

    selectedAllies.clear();
    selectedCommanders.clear();
    std::cout << "Game restarted." << std::endl;
}