#include "simulator/Application.h"

#include "cmake_defines.h"
#include "Logger.h"
#include "simulator/CommandLineData.h"
#include "simulator/MotionModel.h"

#include <CLI11.hpp>

#include <memory>
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

    int parse_command_line_arguments_result = parse_command_line_arguments(argc, argv, command_line_data);
    if (parse_command_line_arguments_result != 0)
    {
        throw std::runtime_error("Failed to parse command-line arguments");
    }

    motion_model = std::make_unique<MotionModel>();
    logger.log_info("Created motion model object at address: %p", motion_model.get());
    motion_model->initialize(command_line_data);
}

Application::~Application() = default;

int Application::parse_command_line_arguments(int argc, char* argv[], CommandLineData& command_line_data) const
{
    CLI::App app("RRS simulator v" APPLICATION_VERSION);
    argv = app.ensure_utf8(argv);

    app.add_option("-t,--train-config", command_line_data.train_configs, "Train configurations");
    app.add_option("-r,--route", command_line_data.route_directory, "Route directory");
    app.add_flag("-c,--clear-log", command_line_data.clear_log, "Clear simulator's log");
    app.add_flag("-o,--debug-print", command_line_data.debug_print, "Allow debug print");
    app.add_option("-x,--init-coord", command_line_data.initial_coordinates, "Initial railway coordinates");
    app.add_option("-d,--direction", command_line_data.directions, "Motion's directions");
    app.add_option("-p,--traj-name", command_line_data.trajectory_names, "Initial trajectory names");

    CLI11_PARSE(app, argc, argv);
    return 0;
}
