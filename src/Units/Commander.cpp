#include "Core/Commander.h"

Commander::Commander(const std::string &name) : Unit(), name(name)
{
    this->isCommander = true;
}

std::string Commander::getName() const
{
    return name;
}
