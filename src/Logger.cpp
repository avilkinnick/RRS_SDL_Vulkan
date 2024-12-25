#include "Logger.h"

#include "cmake_defines.h"

#include <SDL_error.h>

#include <chrono>
#include <exception>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

#define capitalize_fatal FATAL
#define capitalize_error ERROR
#define capitalize_warn WARN
#define capitalize_info INFO
#define capitalize_debug DEBUG
#define capitalize_trace TRACE

#define STRINGIFY(A) #A
#define STRINGIFY_EXPAND(A) STRINGIFY(A)
#define CONCAT(A, B) A##B
#define CONCAT_EXPAND(A, B) CONCAT(A, B)

#define PRINT_CURRENT_TIME(out) \
    { \
        std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
        char* current_time_string = std::ctime(&current_time); \
        current_time_string[strlen(current_time_string) - 1] = '\0'; \
        std::fprintf(out, "[%s] ", current_time_string); \
    }

#define PRINT_LOG_LEVEL(out, log_level) \
    std::fprintf(out, "[%s] ", STRINGIFY_EXPAND(capitalize_##log_level));

#define PRINT_ARGS(out, format, ...); \
    { \
        std::va_list args; \
        va_start(args, format); \
        std::vfprintf(out, format, args); \
        va_end(args); \
    }

#define LOG_IMPLEMENTATION(level, ansi_escape_code) \
    void Logger::log_##level(const char* format, ...) \
    { \
        if (log_to_console) \
        { \
            std::fprintf(stderr, ansi_escape_code); \
            PRINT_CURRENT_TIME(stderr) \
            PRINT_LOG_LEVEL(stderr, level) \
            PRINT_ARGS(stderr, format, __VA_ARGS__) \
            std::fprintf(stderr, "\033[0m\n"); \
        } \
        \
        for (const auto& [log_name, log_descriptor] : log_descriptors) \
        { \
            if (log_descriptor.level_flags & CONCAT_EXPAND(LOG_LEVEL_FLAGS_, capitalize_##level)) \
            { \
                if (log_descriptor.print_time) \
                { \
                    PRINT_CURRENT_TIME(log_descriptor.file) \
                } \
                \
                if (log_descriptor.print_level) \
                { \
                    PRINT_LOG_LEVEL(log_descriptor.file, level); \
                } \
                \
                PRINT_ARGS(log_descriptor.file, format, __VA_ARGS__) \
                std::fprintf(log_descriptor.file, "\n"); \
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
    for (const auto& [log_name, log_descriptor] : log_descriptors)
    {
        std::fclose(log_descriptor.file);
    }
}

void Logger::attach_file(std::string_view filename, LogLevelFlags level_flags, bool print_time, bool print_level)
{
    FILE* log_file = nullptr;

    try
    {
        if (log_descriptors.find(filename) != log_descriptors.end())
        {
            throw std::runtime_error(std::string("Log \"") + filename.data() + "\" is already attached");
        }

        constexpr const char* log_name_regex_string = R"(\w+\.\w+)";
        std::regex log_name_regex(log_name_regex_string);
        if (!std::regex_match(filename.data(), log_name_regex))
        {
            throw std::runtime_error(
                std::string("Invalid filename. Must match regular expression: ") + log_name_regex_string
            );
        }

        std::string log_path = std::string(LOGS_DIR "/") + filename.data();
        log_file = std::fopen(log_path.c_str(), "a");
        if (!log_file)
        {
            throw std::runtime_error(std::string("Failed to open \"") + filename.data() + '\"');
        }

        log_descriptors.emplace(filename, LogDescriptor{log_file, level_flags, print_time, print_level});
    }
    catch (const std::exception& exception)
    {
        if (log_file)
        {
            std::fclose(log_file);
        }

        log_warn(exception.what());
    }
}

void Logger::detach_file(std::string_view filename)
{
    try
    {
        auto found_it = log_descriptors.find(filename);
        if (found_it == log_descriptors.end())
        {
            throw std::runtime_error(std::string("Log \"") + filename.data() + "\" is not attached");
        }

        std::fclose(found_it->second.file);
        log_descriptors.erase(found_it);
    }
    catch (const std::exception& exception)
    {
        log_warn(exception.what());
    }
}

LOG_IMPLEMENTATION(fatal, "\033[1;31m")
LOG_IMPLEMENTATION(error, "\033[1;31m")
LOG_IMPLEMENTATION(warn, "\033[1;33m")
LOG_IMPLEMENTATION(info, "\033[0m")
LOG_IMPLEMENTATION(debug, "\033[0m")
LOG_IMPLEMENTATION(trace, "\033[0m")

void Logger::log_sdl_error()
{
    log_error("SDL error: %s", SDL_GetError());
}
