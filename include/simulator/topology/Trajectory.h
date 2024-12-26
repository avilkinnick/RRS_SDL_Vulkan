#ifndef SIMULATOR_TOPOLOGY_TRAJECTORY_H
#define SIMULATOR_TOPOLOGY_TRAJECTORY_H

#include <string_view>
#include <vector>

struct ModuleDescriptor;

class Trajectory
{
public:
    void load(
        std::string_view route_directory,
        std::string_view trajectory_name,
        std::vector<ModuleDescriptor> modules
    );
};

#endif // SIMULATOR_TOPOLOGY_TRAJECTORY_H
