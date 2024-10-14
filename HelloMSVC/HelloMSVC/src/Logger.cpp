#include "Logger.h"

#include <iostream>

void Logger::setLevel(Level level)
{
    this->level = level;
}

void Logger::logDebug(std::string x)
{
    std::cout << "[DEBUG] " << x << std::endl;
}
