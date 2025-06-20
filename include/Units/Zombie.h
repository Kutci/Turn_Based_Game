#pragma once

#include "Core/Unit.h"

class Zombie : public Unit
{
public:
    Zombie();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;
};