#pragma ocne

#include "Core/Unit.h"

class Ghoul : public Unit
{
public:
    Ghoul();

    void print() const override;
    Unit *clone() const override;
    std::string getTypeName() const override;
    bool isAliveUnit() const override;
};