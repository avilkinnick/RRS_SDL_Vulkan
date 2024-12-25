#ifndef SIMULATOR_TRAIN_MODEL_INITIALIZE_DATA_H
#define SIMULATOR_TRAIN_MODEL_INITIALIZE_DATA_H

#include <string>

#include <cstddef>

// TODO: Change names
// TODO: Separate header?
struct solver_config_t
{
    /// ODE solution method (solver name)
    std::string method = "euler";

    /// Intital time
    double start_time = 0.0;

    /// Stop integration time
    double stop_time = 10.0;

    /// Initial time step value (step value for fixed step methods)
    double step = 3.0e-3;

    /// Maximal step value
    double max_step = 3.0e-3;

    /// Number of substep
    std::size_t num_sub_step = 1;

    /// Local error of solution
    double local_error = 1.0e-5;
};

struct TrainModelInitializeData
{
    std::string route_dir_name = "experimental-polygon";
    std::string train_config = "vl60pk-1543";
    std::string trajectory_name = "route1_0001_1";
    int direction = 1;
    double init_coord = 780.0;
    double init_velocity = 0.0;
    double coeff_to_wheel_rail_friction = 1.0;
    int integration_time_interval = 15;
    int control_time_interval = 15;
    bool debug_print = false;
    solver_config_t solver_config;
};

#endif // SIMULATOR_TRAIN_MODEL_INITIALIZE_DATA_H
