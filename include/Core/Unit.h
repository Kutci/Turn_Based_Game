#pragma once
#include "../Armor/Armor.h"
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
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
    virtual bool isAliveUnit() const = 0;
    virtual Unit *clone() const = 0;
    virtual std::string getTypeName() const = 0;
    virtual std::string getName() const;

    virtual bool sacrifice(Unit *target);
    virtual void heal(Unit *target);
    virtual std::vector<Unit *> summon(const std::vector<Unit *> &deadAllies);

    unsigned getHealth() const;
    unsigned getAttack() const;
    unsigned getMana() const;
    unsigned getGoldCost() const;
    bool getIsCommander() const;
    unsigned getMaxHealth() const;
    unsigned getArmorDurability() const;

    void setHealth(unsigned health);
    void setIsCommander(bool);
    void setMana(unsigned mana);
    void setDurability(unsigned durability);

    void addMana(unsigned mana);

private:
    void copyFrom(const Unit &);
    void free();
};
