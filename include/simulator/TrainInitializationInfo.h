#pragma once

#include "simulator/Solver.h"

#include <string>

struct TrainInitializationInfo
{
    std::string route_directory_name = "experimental-polygon";
    std::string train_config = "vl60pk-1543";
    std::string trajectory_name = "route1_0001_1";
    int direction = 1;
    double initial_coordinate = 780.0;
    double initial_velocity = 0.0;
    double wheel_rail_friction_coefficient = 1.0;
    int integration_time_interval = 15;
    int control_time_interval = 15;
    bool debug_print = false;
    Solver solver;
};

