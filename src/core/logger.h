#pragma once
#include <cstdio>

#define PROTIUM_FATAL(msg) Logger::fatal(msg);
#define PROTIUM_ERROR(msg) Logger::error(msg);
#define PROTIUM_WARN(msg) Logger::warning(msg);
#define PROTIUM_INFO(msg) Logger::info(msg);
#define PROTIUM_TRACE(msg) Logger::trace(msg);

class Logger
{
  public:
    static void fatal(const char *msg);
    static void error(const char *msg);
    static void warning(const char *msg);
    static void info(const char *msg);
    static void trace(const char *msg);
};
