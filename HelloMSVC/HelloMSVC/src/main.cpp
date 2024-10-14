#include <iostream>
#include <memory>
#include <string>

#include "Entity.h"
#include "Logger.h"
#include "Player.h"
#include "Vertex.h"

int main()
{
    Logger logger = Logger(Logger::Debug);

    std::unique_ptr<Entity> player = std::make_unique<Player>("Player 1");
    logger.logDebug(std::string("Name: ") + player->getName());
    logger.logDebug(std::string("Position X: ") + std::to_string(player->getPosition()->getX()));
    logger.logDebug(std::string("Position Y: ") + std::to_string(player->getPosition()->getY()));

    const char *source = R"(
// Comment line 1
// Comment line 2
)";
    logger.logDebug(source);

    logger.logDebug(std::string("Vertex z offset: ") + std::to_string(Vertex::GetOffsetZ()));

    bool doesContain = std::string("Hello").find("Hello") != std::string::npos;
    logger.logDebug("Hello contains Hello" + doesContain ? "Yes" : "No");

    std::cin.get();
}
