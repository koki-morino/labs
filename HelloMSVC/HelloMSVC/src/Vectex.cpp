#include "Vertex.h"

Vertex::Vertex(float x, float y, float z) : x(x), y(y), z(z)
{
}

int Vertex::GetOffsetZ()
{
    return (int)&((Vertex *)nullptr)->z;
}

float Vertex::getX() const
{
    return this->x;
}

float Vertex::getY() const
{
    return this->y;
}

float Vertex::getZ() const
{
    return this->z;
}
