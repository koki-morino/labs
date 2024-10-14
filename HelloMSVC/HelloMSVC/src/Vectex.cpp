#include "Vertex.h"

int Vertex::GetOffsetZ()
{
    return (int)&((Vertex *)nullptr)->z;
}
