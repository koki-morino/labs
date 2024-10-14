#pragma once

#include "Entity.h"
#include <string>

class Player : public Entity
{
  public:
    Player(const std::string &name);
    const char *const getName() const override;
    void setName(const std::string &name) override;
    const Position *const getPosition() override;
    void setPosition(const Position &position) override;
};
