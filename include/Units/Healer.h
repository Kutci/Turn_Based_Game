#pragma once
#include "Core/Unit.h"
#include <string>

class Healer : public Unit
{
public:
    Healer();
    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;

    void heal(Unit *target) override;
};