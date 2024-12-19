#include "simulator/Application.h"

#include "Logger.h"

#include <CLI11.hpp>

#include <stdexcept>
#include <string>

Application::Application(int argc, char* argv[])
{
    std::string command_line_string;
    for (int i = 1; i < argc; ++i)
    {
        command_line_string = command_line_string + ' ' + argv[i];
    }

    Logger& logger = Logger::get_instance();
    logger.log_info("Simulator started with command line:%s", command_line_string.c_str());
    logger.log_info("Started initialization");

    int parse_command_line_arguments_result = parse_command_line_arguments(argc, argv);
    if (parse_command_line_arguments_result != 0)
    {
        throw std::runtime_error(
            std::string("Command line parser failed with error code ")
            + std::to_string(parse_command_line_arguments_result)
        );
    }
}

int Application::parse_command_line_arguments(int argc, char* argv[])
{
    CLI::App app("RRS simulator");
    argv = app.ensure_utf8(argv);

    CLI11_PARSE(app, argc, argv);
    return 0;
}
