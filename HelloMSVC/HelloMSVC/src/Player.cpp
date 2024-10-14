#include "Player.h"

#include <string>

Player::Player(const std::string &name) : Entity(name)
{
}

const char *const Player::getName() const
{
    return this->name.c_str();
}

void Player::setName(const std::string &name)
{
    this->name = name;
}

const Position *const Player::getPosition()
{
    return &this->position;
}

void Player::setPosition(const Position &position)
{
    this->position = position;
}
