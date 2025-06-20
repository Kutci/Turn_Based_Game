#pragma once
#include "Core/Commander.h"

class DreadLord : public Commander
{
private:
    unsigned summonCount = 0;

public:
    DreadLord(const std::string &name);

    void castSpell(std::vector<Unit *> &ownArmy,
                   std::vector<Unit *> &,
                   std::vector<Unit *> &,
                   const std::string &summonType) override;
    bool isAliveUnit() const override;
    std::string getTypeName() const override;
    void print() const override;
    Unit *clone() const override;
};