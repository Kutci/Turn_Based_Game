#pragma once
#include "Core/Unit.h"
#include <string>

class Infantry : public Unit
{

public:
    Infantry();
    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;
};