#include "simulator/TrainModel.h"

#include "cmake_defines.h"
#include "ConfigFile.h"
#include "Logger.h"
#include "simulator/CommandLineData.h"
#include "simulator/TrainModelInitializeData.h"

#include <string>

void TrainModel::initialize(const CommandLineData& command_line_data)
{
    debug_print = command_line_data.debug_print;

    TrainModelInitializeData initialize_data;
    load_initialize_data(initialize_data);
}

void TrainModel::load_initialize_data(TrainModelInitializeData& initialize_data)
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

    initialize_data.debug_print = config_file.read<bool>("DebugPrint");

    logger.log_info("Loaded settings from: %s", config_path.c_str());
}
