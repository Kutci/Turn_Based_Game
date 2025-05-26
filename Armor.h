#pragma once

class Armor
{
protected:
    unsigned durability;

public:
    explicit Armor(unsigned durability);
    virtual ~Armor() {}

    virtual unsigned reduceDamage(unsigned dmg) = 0;

    bool canUse() const;

    void use();
    unsigned getDurability() const;

    virtual Armor *clone() const = 0;
    virtual const char *getTypeName() const = 0;
};
