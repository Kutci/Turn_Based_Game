#pragma once
#include "Zombie.h"

class Revenant : public Zombie
{
public:
    Revenant();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
};