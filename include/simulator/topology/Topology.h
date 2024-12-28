#pragma once

#include <string>
#include <string_view>
#include <vector>

struct ModuleDescriptor;

class Topology
{
public:
    void load(std::string_view route_directory);

private:
    std::vector<std::string> get_trajectory_names(std::string_view route_path);
    std::vector<std::vector<ModuleDescriptor>> load_topology_configs(std::string_view route_path);
};

