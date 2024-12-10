#include "Logger.h"

#include <fstream>
#include <map>
#include <string_view>

std::ostream* Logger::current_log = nullptr;

Logger& Logger::get_instance()
{
    static Logger logger;
    return logger;
}

void Logger::set_current_log(std::string_view log_name)
{
    auto found_it = logs.find(log_name);
    if (found_it != logs.end())
    {

    }
}
