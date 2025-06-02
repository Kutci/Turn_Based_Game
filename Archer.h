#pragma once
#include "Unit.h"
#include <string>

class Archer : public Unit
{
public:
    Archer();
    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
};