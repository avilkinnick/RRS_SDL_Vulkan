#pragma once

#include "simulator/topology/Track.h"

#include <string>
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

private:
    std::string name;
    double length = 0.0;
    std::vector<Track> tracks;
};
