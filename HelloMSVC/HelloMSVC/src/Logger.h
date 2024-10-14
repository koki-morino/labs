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

    void setLevel(Level level);

    void logDebug(std::string x);

  private:
    Level level = Info;
};
