#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <map>
#include <string_view>

#include "logging/LogCategoryFlags.h"
#include "logging/LogDescriptor.h"

class Logger
{
public:
    static Logger& get_instance();
    ~Logger();

    void attach_log(std::string_view log_name, LogCategoryFlags category_flags = LogCategoryFlags::all);
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
    bool log_time = false;

private:
    Logger() = default;

private:
    std::map<std::string_view, LogDescriptor> log_descriptors;
};

#endif // LOGGING_LOGGER_H
