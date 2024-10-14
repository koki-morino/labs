#include <iostream>

#include "Entity.h"
#include "Logger.h"
#include "Player.h"

int main()
{
    Logger logger = Logger();
    Entity* player = new Player();

    logger.logDebug(player->getName());
    std::cin.get();
}
