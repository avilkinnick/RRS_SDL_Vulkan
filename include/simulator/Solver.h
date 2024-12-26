#ifndef SIMULATOR_SOLVER_H
#define SIMULATOR_SOLVER_H

#include <string>

#include <cstddef>

struct Solver
{
    std::string method = "euler"; //< ODE solution method (solver name)
    double start_time = 0.0; //< Initital time
    double stop_time = 10.0; //< Stop integration time
    double step = 3.0e-3; //< Initial time step value (step value for fixed step methods)
    double max_step = 3.0e-3; //< Maximal step value
    std::size_t sub_step_count = 1; //< Substep count
    double local_error = 1.0e-5; //< Local error of solution
};

#endif // SIMULATOR_SOLVER_H
