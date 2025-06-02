#pragma once
#include "Unit.h"
#include <string>

class Healer : public Unit
{
public:
    Healer();
    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;

    void heal(Unit *target);
};