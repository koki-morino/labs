#include "Logger.h"

#include <iostream>

Logger::Logger() : level(Info)
{
}

Logger::Logger(Level level) : level(level)
{
}

void Logger::setLevel(const Level level)
{
    this->level = level;
}

void Logger::logDebug(const std::string &x) const
{
    if (this->level >= Logger::Debug)
        std::cout << "[DEBUG] " << x << std::endl;
}
