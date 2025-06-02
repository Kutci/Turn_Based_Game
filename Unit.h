#pragma once
#include "Armor.h"
#include <cstring>
#include <string>

class Unit
{
protected:
    unsigned health;
    unsigned maxHealth;
    unsigned attack;
    unsigned goldCost;
    unsigned mana;
    Armor *armor = nullptr;
    bool isCommander;

public:
    Unit();
    Unit(const Unit &other);
    Unit &operator=(const Unit &);
    virtual ~Unit();
    virtual void takeDamage(unsigned dmg);
    virtual void attackEnemy(Unit *target);
    virtual void print() const = 0;
    virtual bool isAlive() const;
    virtual Unit *clone() const = 0;
    virtual std::string getTypeName() const = 0;

    unsigned getHealth() const;
    unsigned getAttack() const;
    unsigned getMana() const;
    bool getIsCommander() const;

    void setHealth(unsigned health);

private:
    void copyFrom(const Unit &);
    void free();
};
