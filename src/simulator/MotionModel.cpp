#include "simulator/MotionModel.h"

#include "cmake_defines.h"
#include "ConfigFile.h"
#include "Logger.h"
#include "simulator/CommandLineData.h"
#include "simulator/TrainInitializeData.h"

#include <string>

#include <cstddef>

void MotionModel::initialize(const CommandLineData& command_line_data)
{
    debug_print = command_line_data.debug_print;

    TrainInitializeData initialize_data;
    load_initialize_data(initialize_data);
    override_initialize_data_by_command_line(initialize_data, command_line_data);
}

void MotionModel::load_initialize_data(TrainInitializeData& initialize_data)
{
    Logger& logger = Logger::get_instance();
    logger.log_info("==== Initialize data loading ====");

    std::string config_path = std::string(CONFIGS_DIR "/") + "init-data.xml";
    ConfigFile config_file(config_path);
    config_file.set_current_section("InitData");

    initialize_data.route_dir_name = config_file.read<std::string>("RouteDirectory");
    initialize_data.train_config = config_file.read<std::string>("TrainConfig");
    initialize_data.trajectory_name = config_file.read<std::string>("TrajectoryName");
    initialize_data.direction = config_file.read<int>("Direction");
    initialize_data.init_coord = config_file.read<double>("InitCoord");
    initialize_data.init_velocity = config_file.read<double>("InitVelocity");
    initialize_data.coeff_to_wheel_rail_friction = config_file.read<double>("CoeffToWheelRailFriction");
    initialize_data.integration_time_interval = config_file.read<int>("IntegrationTimeInterval");
    initialize_data.control_time_interval = config_file.read<int>("ControlTimeInterval");

    // control_delay = static_cast<double>(init_data.control_time_interval) / 1000.0;

    logger.log_info("Loaded settings from: %s", config_path.c_str());
}

void MotionModel::override_initialize_data_by_command_line(
    TrainInitializeData& initialize_data,
    const CommandLineData& command_line_data
)
{
    Logger& logger = Logger::get_instance();
    logger.log_info("==== Command line processing ====");

    if (command_line_data.route_dir)
    {
        initialize_data.route_dir_name = command_line_data.route_dir.value();
    }

    initialize_data.debug_print = command_line_data.debug_print;

    if (!command_line_data.train_config)
    {
        logger.log_info("Command line is empty. Apply init_data.xml config");
        return;
    }

    train_initialize_datas.clear();

    for (std::size_t i = 0; i < command_line_data.train_config->size(); ++i)
    {
        TrainInitializeData train_initialize_data;
        train_initialize_data.route_dir_name = initialize_data.route_dir_name;
        train_initialize_data.train_config = command_line_data.train_config->at(i);

        if (command_line_data.init_coord)
        {
            train_initialize_data.init_coord = command_line_data.init_coord->at(i);
        }

        if (command_line_data.direction)
        {
            train_initialize_data.direction = command_line_data.direction->at(i);
        }

        if (command_line_data.trajectory_name)
        {
            train_initialize_data.trajectory_name = command_line_data.trajectory_name->at(i);
        }

        train_initialize_datas.push_back(train_initialize_data);
    }

    logger.log_info("Apply command line settings");
}
