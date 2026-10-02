#include "logger.h"

enum log_levels
{
    FATAL,
    ERROR,
    WARNING,
    INFO,
    TRACE,
    LOG_LEVEL_COUNT
};
const char *log_level_name[LOG_LEVEL_COUNT] = {"\033[31;40m[FATAL]:  \033[0m ", "\033[31m[ERROR]:   \033[0m", "\033[33m[WARNING]: \033[0m",
                                               "\033[32m[INFO]:   \033[0m ", "\033[36m[TRACE]:  \033[0m "};

void Logger::fatal(const char *msg)
{
    printf("%s%s\n", log_level_name[FATAL], msg);
};
void Logger::error(const char *msg)
{
    printf("%s%s\n", log_level_name[ERROR], msg);
};
void Logger::warning(const char *msg)
{
    printf("%s%s\n", log_level_name[WARNING], msg);
};
void Logger::info(const char *msg)
{
    printf("%s%s\n", log_level_name[INFO], msg);
};
void Logger::trace(const char *msg)
{
    printf("%s%s\n", log_level_name[TRACE], msg);
};
