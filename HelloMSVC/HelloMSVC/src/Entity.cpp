#include "Entity.h"

#include <string>

void Entity::move(float x, float y)
{
    this->x = x;
    this->y = y;
}

std::string Entity::getName()
{
    return "Entity";
}
