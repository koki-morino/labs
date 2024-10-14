#pragma once

#include "Position.h"
#include <string>

class Entity
{
  protected:
    std::string name;
    Position position;
    int speed;

  public:
    Entity(const std::string &name);
    Entity(const std::string &name, const Position position);
    virtual const char *const getName() const = 0;
    virtual void setName(const std::string &name) = 0;
    virtual const Position *const getPosition() = 0;
    virtual void setPosition(const Position &position) = 0;
};
