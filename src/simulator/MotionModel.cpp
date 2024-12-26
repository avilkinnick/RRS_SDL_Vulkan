#include "simulator/MotionModel.h"

#include "cmake_defines.h"
#include "ConfigFile.h"
#include "Logger.h"
#include "simulator/CommandLineData.h"
#include "simulator/Solver.h"
#include "simulator/TrainInitializationInfo.h"
#include "simulator/topology/Topology.h"

#include <memory>
#include <string>
#include <vector>

#include <cstddef>

MotionModel::MotionModel() = default;
MotionModel::~MotionModel() = default;

void MotionModel::initialize(const CommandLineData& command_line_data)
{
    debug_print = command_line_data.debug_print;

    TrainInitializationInfo train_initialization_info;
    load_train_initialization_info(train_initialization_info);
    train_initialization_infos.emplace_back(train_initialization_info);

    override_train_initialization_info_by_command_line(train_initialization_info, command_line_data);

    config_solver(train_initialization_info.solver);

    initialize_topology(train_initialization_info);
}

void MotionModel::load_train_initialization_info(TrainInitializationInfo& train_initialization_info)
{
    Logger& logger = Logger::get_instance();
    logger.log_info("==== Initialize data loading ====");

    std::string config_path = std::string(CONFIGS_DIR "/") + "init-data.xml";
    ConfigFile config_file(config_path);
    config_file.set_current_section("InitData");

    train_initialization_info.route_directory_name = config_file.read<std::string>("RouteDirectory");
    train_initialization_info.train_config = config_file.read<std::string>("TrainConfig");
    train_initialization_info.trajectory_name = config_file.read<std::string>("TrajectoryName");
    train_initialization_info.direction = config_file.read<int>("Direction");
    train_initialization_info.initial_coordinate = config_file.read<double>("InitCoord");
    train_initialization_info.initial_velocity = config_file.read<double>("InitVelocity");
    train_initialization_info.wheel_rail_friction_coefficient = config_file.read<double>("CoeffToWheelRailFriction");
    train_initialization_info.integration_time_interval = config_file.read<int>("IntegrationTimeInterval");
    train_initialization_info.control_time_interval = config_file.read<int>("ControlTimeInterval");

    control_delay = static_cast<double>(train_initialization_info.control_time_interval) / 1000.0;

    train_initialization_info.debug_print = config_file.read<bool>("DebugPrint");

    logger.log_info("Loaded settings from: %s", config_path.c_str());
}

void MotionModel::override_train_initialization_info_by_command_line(
    TrainInitializationInfo& train_initialization_info,
    const CommandLineData& command_line_data
)
{
    Logger& logger = Logger::get_instance();
    logger.log_info("==== Command line processing ====");

    if (command_line_data.route_directory_name)
    {
        train_initialization_info.route_directory_name = command_line_data.route_directory_name.value();
    }

    train_initialization_info.debug_print = command_line_data.debug_print;

    if (!command_line_data.train_configs)
    {
        logger.log_info("Command line is empty. Apply init_data.xml config");
        return;
    }

    train_initialization_infos.clear();

    // TODO: Change name
    TrainInitializationInfo id;
    id.route_directory_name = train_initialization_info.route_directory_name;

    for (std::size_t i = 0, train_config_count = command_line_data.train_configs->size(); i < train_config_count; ++i)
    {
        id.train_config = command_line_data.train_configs->at(i);

        if (command_line_data.initial_coordinates)
        {
            id.initial_coordinate = command_line_data.initial_coordinates->at(i);
        }

        if (command_line_data.directions)
        {
            id.direction = command_line_data.directions->at(i);
        }

        if (command_line_data.trajectory_names)
        {
            id.trajectory_name = command_line_data.trajectory_names->at(i);
        }

        train_initialization_infos.push_back(id);
    }

    logger.log_info("Apply command line settings");
}

void MotionModel::config_solver(Solver& solver) const
{
    Logger& logger = Logger::get_instance();
    logger.log_info("==== Solver configuration ====");\

    ConfigFile config_file(std::string(CONFIGS_DIR "/") + "solver.xml");
    config_file.set_current_section("Solver");

    solver.integration_method = config_file.read<std::string>("Method");
    solver.start_time = config_file.read<double>("StartTime");
    solver.stop_time = config_file.read<double>("StopTime");
    solver.step = config_file.read<double>("InitStep");
    solver.max_step = config_file.read<double>("MaxStep");
    solver.sub_step_count = config_file.read<int>("SubStepNum");
    solver.local_error = config_file.read<double>("LocalError");

    logger.log_info("Integration method: %s", solver.integration_method.c_str());
    logger.log_info("Start time: %f", solver.start_time);
    logger.log_info("Stop time: %f", solver.stop_time);
    logger.log_info("Initial integration step: %f", solver.step);
    logger.log_info("Maximal integration step: %f", solver.max_step);
    logger.log_info("Number of substep: %f", solver.sub_step_count);
    logger.log_info("Local error of solution: %f", solver.local_error);
}

void MotionModel::initialize_topology(TrainInitializationInfo& train_initialization_info)
{
    Logger& logger = Logger::get_instance();
    logger.log_info("==== Route topology loading ====");

    topology = std::make_unique<Topology>();
    topology->load(train_initialization_info.route_directory_name);
}
