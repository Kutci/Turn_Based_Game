#pragma once

#include "Zombie.h"

class Dibbuk : public Zombie
{
public:
    Dibbuk();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
};