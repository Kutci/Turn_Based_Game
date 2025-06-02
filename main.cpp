#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Infantry.h"
#include "Knight.h"
#include "Healer.h"
#include "Archer.h"
#include "Mage.h"
bool hasAliveEnemies(const std::vector<Unit *> &enemies)
{
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        if (enemies[i]->isAlive())
        {
            return true;
        }
    }
    return false;
}
int main()
{
    std::srand(std::time(0));

    std::vector<Unit *> units;
    units.push_back(new Infantry());
    units.push_back(new Knight());
    units.push_back(new Healer());
    units.push_back(new Archer());
    units.push_back(new Mage());

    std::vector<Unit *> enemies;
    for (Unit *u : units)
        enemies.push_back(u->clone());

    std::cout << "=== Original Units ===\n";
    for (Unit *u : units)
        u->print();

    std::cout << "\n=== Enemy Units ===\n";
    for (Unit *e : enemies)
        e->print();

    std::cout << "\n=== Battle Simulation ===\n";

    for (size_t i = 0; i < units.size(); ++i)
    {
        Unit *attacker = units[i];

        if (!hasAliveEnemies(enemies))
        {
            std::cout << "All enemies are defeated!\n";
            break;
        }

        Unit *target = enemies[std::rand() % enemies.size()];
        std::cout << "\n"
                  << attacker->getTypeName() << " attacks " << target->getTypeName() << "!\n";

        attacker->attackEnemy(target);
    }

    std::cout << "\n=== Enemy Units After Attack ===\n";
    for (Unit *e : enemies)
        e->print();

    std::cout << "\n=== Original Units After Attack===\n";
    for (Unit *u : units)
        u->print();

    for (Unit *u : units)
        delete u;
    for (Unit *e : enemies)
        delete e;

    return 0;
}
