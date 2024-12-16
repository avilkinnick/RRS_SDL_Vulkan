#include "logging/LogDescriptor.h"

LogDescriptor::LogDescriptor(FILE* file, LogCategoryFlags category_flags)
    : file(file)
    , category_flags(category_flags)
{
}

LogDescriptor::~LogDescriptor()
{
}
