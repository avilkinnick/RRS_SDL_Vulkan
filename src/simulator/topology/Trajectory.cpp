#include "simulator/topology/Trajectory.h"

#include "simulator/topology/ModuleDescriptor.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

void Trajectory::load(
    std::string_view route_directory,
    std::string_view trajectory_name,
    std::vector<ModuleDescriptor> modules
)
{
    std::string path = std::string(route_directory) + "/topology/trajectories/" + trajectory_name.data() + ".traj";

    std::ifstream file(path);
    if (!file)
    {
        throw std::runtime_error(std::string("Path \"" + path +" \" not found"));
    }
}
