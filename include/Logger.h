#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>

#include <map>
#include <string_view>

class Logger
{
public:
    static Logger& get_instance();
    ~Logger();

    void enable_console_log() { log_to_console = true; }
    void disable_console_log() { log_to_console = false; }

    void attach_log(std::string_view log_name);
    void detach_log(std::string_view log_name);

    void log_error(const char* format, ...);
    void log_warning(const char* format, ...);
    void log_message(const char* format, ...);

#ifndef NDEBUG
    void log_debug(const char* format, ...);
#else
    void log_debug(const char* format, ...) {}
#endif

    void log_sdl_error();

private:
    Logger() = default;

private:
    bool log_to_console = true;
    std::map<std::string_view, FILE*> log_files;
};

#endif // LOGGER_H
