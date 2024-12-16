#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <map>
#include <string_view>

#include <cstdio>

enum LogLevelFlags
{
    LOG_LEVEL_FLAGS_CRITICAL = 0x01,
    LOG_LEVEL_FLAGS_ERROR = 0x01,
    LOG_LEVEL_FLAGS_WARNING = 0x01,
    LOG_LEVEL_FLAGS_INFO = 0x01,
    LOG_LEVEL_FLAGS_DEBUG = 0x01,
    LOG_LEVEL_FLAGS_VERBOSE = 0x01,

    LOG_CATEGORY_FLAGS_ALL =
        LOG_CATEGORY_FLAGS_ERROR
        | LOG_CATEGORY_FLAGS_WARNING
        | LOG_CATEGORY_FLAGS_INFO
        | LOG_CATEGORY_FLAGS_DEBUG
};

struct LogDescriptor
{
    FILE* file;
    LogCategoryFlags category_flags;
    bool print_time;
};

class Logger
{
public:
    static Logger& get_instance();
    ~Logger();

    void attach_log(
        std::string_view log_name,
        LogCategoryFlags category_flags = LOG_CATEGORY_FLAGS_ALL,
        bool print_time = true
    );

    void detach_log(std::string_view log_name);

    void log_error(const char* format, ...);
    void log_warning(const char* format, ...);
    void log_info(const char* format, ...);
    void log_message(const char* format, ...);

#ifndef NDEBUG
    void log_debug(const char* format, ...);
#else
    void log_debug(const char* format, ...) {}
#endif

    void log_sdl_error();

public:
    static constexpr const char* separator = "========================================================================";

    bool log_to_console = true;

private:
    Logger() = default;

private:
    std::map<std::string_view, LogDescriptor> log_descriptors;
};

#endif // LOGGING_LOGGER_H
