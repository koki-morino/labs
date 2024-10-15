#pragma once

class Vertex
{
  private:
    float x, y, z;

  public:
    Vertex(float x, float y, float z);
    static int GetOffsetZ();
    float getX() const;
    float getY() const;
    float getZ() const;
};
