#pragma once

#include "Entity.h"
#include <string>

class Player : public Entity
{
  public:
    std::string getName() override;
};
