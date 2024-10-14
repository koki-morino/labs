#pragma once

class Position final
{
  private:
    float x;
    float y;

  public:
    Position();
    explicit Position(float x, float y);
    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
};
