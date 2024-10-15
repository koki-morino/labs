#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Entity.h"
#include "Logger.h"
#include "Player.h"
#include "Vertex.h"

int main()
{
    Logger logger = Logger(Logger::Debug);

    std::unique_ptr<Entity> player = std::make_unique<Player>("Player 1");
    logger.logDebug("Name: " + std::string(player->getName()));
    logger.logDebug("Position X: " + std::to_string(player->getPosition()->getX()));
    logger.logDebug("Position Y: " + std::to_string(player->getPosition()->getY()));

    logger.logDebug("Vertex z offset: " + std::to_string(Vertex::GetOffsetZ()));

    std::vector<Vertex> vertices;
    vertices.reserve(3);

    vertices.emplace_back(1.f, 1.f, 1.f);
    vertices.emplace_back(1.f, 1.f, 1.f);
    vertices.emplace_back(1.f, 1.f, 1.f);

    for (Vertex &vertex : vertices)
    {
        logger.logDebug("Vertex x: " + std::to_string(vertex.getX()));
    }

    const char *source = R"(
// Comment line 1
// Comment line 2
)";
    logger.logDebug(source);

    bool doesContain = std::string("Hello").find("Hello") != std::string::npos;
    logger.logDebug("Hello contains Hello" + doesContain ? "Yes" : "No");

    std::cin.get();
}
