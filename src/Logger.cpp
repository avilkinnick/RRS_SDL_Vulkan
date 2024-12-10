#include "Logger.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

#include "cmake_defines.h"

std::ostream* Logger::current_log = &std::cerr;

Logger& Logger::get_instance()
{
    static Logger logger;
    return logger;
}

void Logger::set_current_log(std::string_view log_name)
{
    if (log_name.empty())
    {
        set_current_log_console();
        return;
    }

    auto found_it = logs.find(log_name);
    if (found_it != logs.end())
    {
        current_log = &found_it->second;
        return;
    }

    // std::ofstream log(std::string(LOGS_DIR "/") + log_name.data())
}

void Logger::set_current_log_console()
{
    current_log = &std::cerr;
}
