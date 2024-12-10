#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <map>
#include <string_view>

class Logger
{
public:
    static Logger& get_instance();

    static void set_current_log(std::string_view log_name);
    static void set_current_log_console();

private:
    Logger() = default;

private:
    static std::map<std::string_view, std::ofstream> logs;
    static std::ostream* current_log;
};

#endif // LOGGER_H
