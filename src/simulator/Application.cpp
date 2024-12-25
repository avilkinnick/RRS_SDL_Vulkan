#include "simulator/Application.h"

#include "Logger.h"
#include "simulator/CommandLineData.h"

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

    CommandLineData command_line_data;
    parse_command_line_arguments(argc, argv, command_line_data);
}

void Application::parse_command_line_arguments(int argc, char* argv[], CommandLineData& command_line_data)
{
    CLI::App app("RRS simulator v1.5.0");
    argv = app.ensure_utf8(argv);

    app.add_option("-t,--train-config", command_line_data.train_config, "Train configuration");
    app.add_option("-r,--route", command_line_data.route_dir, "Route directory");
    app.add_option("-c,--clear-log", command_line_data.clear_log, "Clear simulator's log");
    app.add_option("-o,--debug-print", command_line_data.debug_print, "Allow debug print");
    app.add_option("-x,--init-coord", command_line_data.init_coord, "Initial railway coordinate");
    app.add_option("-d,--direction", command_line_data.direction, "Motion's direction");
    app.add_option("-p,--traj-name", command_line_data.trajectory_name, "Initial trajectory name");

    try
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& error)
    {
        if (app.exit(error) != static_cast<int>(CLI::ExitCodes::Success))
        {
            throw std::runtime_error("Wrong command-line arguments");
        }
    }
}
