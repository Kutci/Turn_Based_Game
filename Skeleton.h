#pragma once
#include "Unit.h"

class Skeleton : public Unit
{
public:
    Skeleton();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
};
