#ifndef LOGGER_H
#define LOGGER_H

#include <map>
#include <string_view>

#include <cstdio>

enum LogLevelFlags
{
    LOG_LEVEL_FLAGS_FATAL = 0x01,
    LOG_LEVEL_FLAGS_ERROR = 0x02,
    LOG_LEVEL_FLAGS_WARN = 0x04,
    LOG_LEVEL_FLAGS_INFO = 0x08,
    LOG_LEVEL_FLAGS_DEBUG = 0x10,
    LOG_LEVEL_FLAGS_TRACE = 0x20,

    LOG_LEVEL_FLAGS_ALL =
        LOG_LEVEL_FLAGS_FATAL
        | LOG_LEVEL_FLAGS_ERROR
        | LOG_LEVEL_FLAGS_WARN
        | LOG_LEVEL_FLAGS_INFO
        | LOG_LEVEL_FLAGS_DEBUG
        | LOG_LEVEL_FLAGS_TRACE
};

struct LogDescriptor
{
    FILE* file;
    LogLevelFlags level_flags;
    bool print_time;
    bool print_level;
};

class Logger
{
public:
    static Logger& get_instance();
    ~Logger();

    void attach_file(
        std::string_view filename,
        LogLevelFlags level_flags = LOG_LEVEL_FLAGS_ALL,
        bool print_time = true,
        bool print_level = true
    );

    void detach_file(std::string_view filename);

    void log_fatal(const char* format, ...);
    void log_error(const char* format, ...);
    void log_warn(const char* format, ...);
    void log_info(const char* format, ...);
    void log_debug(const char* format, ...);
    void log_trace(const char* format, ...);

    void log_sdl_error();

public:
    static constexpr const char* separator = "========================================================================";

    bool log_to_console = true;

private:
    Logger() = default;

private:
    std::map<std::string_view, LogDescriptor> log_descriptors;
};

#endif // LOGGER_H
