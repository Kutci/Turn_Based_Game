#include <iostream>
#include <vector>
#include "Infantry.h"
#include "Unit.h"
int main()
{
    std::vector<Unit *> units;
    units.push_back(new Infantry());

    for (Unit *u : units)
        u->print();

    for (Unit *u : units)
        delete u;
}
