#include "logging/Logger.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

#include <chrono>
#include <exception>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>

#include <SDL_error.h>

#include "cmake_defines.h"

#define LOG_IMPLEMENTATION(category, ansi_escape_code) \
    void Logger::log_##category(const char* format, ...) \
    { \
        char* current_time_string; \
        if (log_time) \
        { \
            std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
            current_time_string = std::ctime(&current_time); \
            current_time_string[strlen(current_time_string) - 1] = '\0'; \
        } \
        \
        if (log_to_console) \
        { \
            std::fprintf(stderr, ansi_escape_code); \
            if (log_time) \
            { \
                std::fprintf(stderr, "[%s] ", current_time_string); \
            } \
            std::va_list args; \
            va_start(args, format); \
            std::vfprintf(stderr, format, args); \
            va_end(args); \
            std::fprintf(stderr, "\033[0m\n"); \
        } \
        \
        for (auto& [log_name, log_descriptor] : log_descriptors) \
        { \
            if (log_file.category_flags & LogCategoryFlags::##category) \
            { \
                std::va_list args; \
                va_start(args, format); \
                if (log_time) \
                { \
                    std::fprintf(log_file.file, "[%s] ", current_time_string); \
                } \
                std::vfprintf(log_file.file, format, args); \
                std::fprintf(log_file.file, "\n"); \
                va_end(args); \
            } \
        } \
    }

Logger& Logger::get_instance()
{
    static Logger logger;
    return logger;
}

Logger::~Logger()
{
    for (auto& [log_name, log_file] : log_files)
    {
        std::fclose(log_file.file);
    }
}

void Logger::attach_log(std::string_view log_name, LogCategoryFlags category_flags)
{
    try
    {
        if (log_files.find(log_name) != log_files.end())
        {
            throw std::runtime_error(std::string("Log \"") + log_name.data() + "\" already attached");
        }

        constexpr const char* log_name_regex_string = R"(\w+\.\w+)";
        std::regex log_name_regex(log_name_regex_string);
        if (!std::regex_match(log_name.data(), log_name_regex))
        {
            throw std::runtime_error(
                std::string("Wrong log name. Must match regular expression: ") + log_name_regex_string
            );
        }

        std::string log_path = std::string(LOGS_DIR "/") + log_name.data();
        FILE* log_file = std::fopen(log_path.c_str(), "a");
        if (!log_file)
        {
            throw std::runtime_error(std::string("Failed to open \"") + log_name.data() + '\"');
        }

        log_files.emplace(log_name, LogFile{log_file, category_flags});
    }
    catch (const std::exception& exception)
    {
        log_warning(exception.what());
    }
}

void Logger::detach_log(std::string_view log_name)
{
    try
    {
        auto found_it = log_files.find(log_name);
        if (found_it == log_files.end())
        {
            throw std::runtime_error(std::string("Log \"") + log_name.data() + "\" not attached");
        }

        std::fclose(found_it->second.file);
        log_files.erase(found_it);
    }
    catch (const std::exception& exception)
    {
        log_error(exception.what());
    }
}

LOG_IMPLEMENTATION(error, "\033[1;31m")
LOG_IMPLEMENTATION(warning, "\033[1;33m")
LOG_IMPLEMENTATION(info, "\033[0m")
LOG_IMPLEMENTATION(message, "\033[0m")

#ifndef NDEBUG
    LOG_IMPLEMENTATION(debug, "\033[0m")
#endif

void Logger::log_sdl_error()
{
    log_error("SDL error: %s", SDL_GetError());
}
