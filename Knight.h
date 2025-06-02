#pragma once
#include "Unit.h"
#include <string>

class Knight : public Unit
{
public:
    Knight();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;

    Armor *getArmor() const;
};