#pragma once
#include <cstdio>

class Logger {
public:
  void error(const char *msg) { printf("%s", msg); }
};

Logger logger;
