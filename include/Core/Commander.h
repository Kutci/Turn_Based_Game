#pragma once

#include "Unit.h"
#include "GameEngine.h"
class Commander : public Unit
{
protected:
    std::string name;

public:
    Commander(const std::string &name);

    virtual void castSpell(
        std::vector<Unit *> &ownArmy,
        std::vector<Unit *> &enemyArmy,
        std::vector<Unit *> &graveyard,
        const std::string &extraInfo = "") = 0;

    bool isAliveUnit() const = 0;
    std::string getTypeName() const = 0;
    void print() const = 0;

    std::string getName() const override;

    virtual Unit *clone() const = 0;
};