#include "Position.h"

Position::Position() : x(0.f), y(0.f)
{
}

Position::Position(float x, float y) : x(x), y(y)
{
}

float Position::getX() const
{
    return this->x;
}

void Position::setX(float x)
{
    this->x = x;
}

float Position::getY() const
{
    return this->y;
}

void Position::setY(float y)
{
    this->y = y;
}
