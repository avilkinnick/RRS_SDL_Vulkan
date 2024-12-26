#ifndef SIMULATOR_MOTION_MODEL_H
#define SIMULATOR_MOTION_MODEL_H

#include <memory>
#include <vector>

struct CommandLineData;
struct Solver;
class Topology;
struct TrainInitializationInfo;

class MotionModel
{
public:
    MotionModel();
    ~MotionModel();

    void initialize(const CommandLineData& command_line_data);

private:
    void load_train_initialization_info(TrainInitializationInfo& train_initialization_info);

    void override_train_initialization_info_by_command_line(
        TrainInitializationInfo& train_initialization_info,
        const CommandLineData& command_line_data
    );

    void config_solver(Solver& solver) const;

    // TODO: Why it accepts TrainInitializationInfo?
    void initialize_topology(TrainInitializationInfo& train_initialization_info);

private:
    double current_time = 0.0; //< Current simulation time
    double current_time_step = 1.0e-3; //< Current simulation time step
    double current_integraion_time = 0.0; //< Current simulation time in current integration interval
    double start_time = 0.0; //< Simulation start time
    double stop_time = 1000.0; //< Simulation stop time
    bool is_step_correct = true; //< Flag of integration step is correct
    bool is_simulation_started = false; //< Flag is simulation thread started
    int realtime_delay = 0; //< Delay for realtime simulation
    int integration_time_interval = 100; //< Minimal intergation interval
    bool debug_print = false; //< Flag, which allow debug print

    // TODO: Add comments
    double control_time = 0.0;
    double control_delay = 0.05;

    int current_vehicle = -1; //< Vehicle which selected by user for view
    int controlled_vehicle = -1; //< Vehicle which selected by user for control
    int previous_controlled_vehicle = -1;

    std::vector<TrainInitializationInfo> train_initialization_infos;
    std::unique_ptr<Topology> topology;
};

#endif // SIMULATOR_MOTION_MODEL_H
