#pragma once

#include <string>

class Entity
{
  public:
    void move(float x, float y);
    virtual std::string getName() = 0;

  protected:
    float x, y;
    std::string name;
};
