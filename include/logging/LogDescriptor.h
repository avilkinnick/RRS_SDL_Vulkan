#ifndef LOGGING_LOG_DESCRIPTOR
#define LOGGING_LOG_DESCRIPTOR

#include <cstdio>

#include "logging/LogCategoryFlags.h"
struct LogDescriptor
{
    FILE* file;
    LogCategoryFlags category_flags;
};

#endif // LOGGING_LOG_DESCRIPTOR
