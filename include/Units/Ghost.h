#pragma once
#include "Core/Unit.h"

class Ghost : public Unit
{
public:
    Ghost();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;

    bool sacrifice(Unit *target) override;
};