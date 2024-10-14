#include "Entity.h"

Entity::Entity(const std::string &name) : name(name), position(Position()), speed(0)
{
}

Entity::Entity(const std::string &name, const Position position) : name(name), position(position), speed(0)
{
}
