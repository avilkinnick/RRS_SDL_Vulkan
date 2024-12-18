#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <map>
#include <string_view>

struct CommandLineBooleanOption
{
    std::string_view short_name;
    std::string_view long_name;
    const char* description;
};

class CommandLineOption
{
    std::string_view short_name;
    std::string_view long_name;
    const char* description;
};

class CommandLineParser
{
public:
    void add_boolean_option(const char* name, const char* short_name, const char* long_name, const char* description);
    void add_option(const char* name, const char* short_name, const char* long_name, const char* description);

private:
    std::map<std::string_view, CommandLineBooleanOption> boolean_options;
    std::map<std::string_view, CommandLineOption> options;
};

#endif // COMMAND_LINE_PARSER_H
