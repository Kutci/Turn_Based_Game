#pragma once
#include "Unit.h"
class Infantry : public Unit
{

public:
    Infantry();
    void print() const override;
    Unit *clone() const override;
};