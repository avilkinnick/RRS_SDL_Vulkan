#include "simulator/Application.h"

#include "Logger.h"
#include "simulator/CommandLineData.h"
#include "simulator/TrainModel.h"

#include <CLI11.hpp>

#include <SDL_assert.h>
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

    train_model = std::make_unique<TrainModel>();
    logger.log_info("Created train model object at address: %p", train_model.get());
    train_model->initialize(command_line_data);
}

Application::~Application() = default;

// TODO: Change names
int Application::parse_command_line_arguments(int argc, char* argv[], CommandLineData& command_line_data)
{
    CLI::App app("RRS simulator v1.5.0");
    argv = app.ensure_utf8(argv);

    app.add_option("-t,--train-config", command_line_data.train_config, "Train configuration");
    app.add_option("-r,--route", command_line_data.route_dir, "Route directory");
    app.add_flag("-c,--clear-log", command_line_data.clear_log, "Clear simulator's log");
    app.add_flag("-o,--debug-print", command_line_data.debug_print, "Allow debug print");
    app.add_option("-x,--init-coord", command_line_data.init_coord, "Initial railway coordinate");
    app.add_option("-d,--direction", command_line_data.direction, "Motion's direction");
    app.add_option("-p,--traj-name", command_line_data.trajectory_name, "Initial trajectory name");

    CLI11_PARSE(app, argc, argv);
    return 0;
}
