#pragma once

#include <string>

class Logger final
{
  public:
    enum Level
    {
        Error,
        Warning,
        Info,
        Debug,
    };

  private:
    Level level;

  public:
    Logger();
    Logger(const Logger &logger) = delete;
    explicit Logger(Level level);
    void setLevel(const Level level);
    void logDebug(const std::string &x) const;
};
