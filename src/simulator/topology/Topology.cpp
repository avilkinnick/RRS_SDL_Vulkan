#include "simulator/topology/Topology.h"

#include "cmake_defines.h"
#include "Logger.h"
#include "simulator/topology/ModuleDescriptor.h"

#include <filesystem>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

void Topology::load(std::string_view route_directory_name)
{
    Logger& logger = Logger::get_instance();

    std::string route_path = std::string(ROUTES_DIR "/") + route_directory_name.data();

    std::vector<std::string> trajectory_names = get_trajectory_names(route_path);
    if (trajectory_names.empty())
    {
        throw std::runtime_error("Trajectories not found");
    }

    // std::vector<std::vector<ModuleDescriptor>> all_modules;
}

std::vector<std::string> Topology::get_trajectory_names(std::string_view route_path)
{
    Logger& logger = Logger::get_instance();

    std::string path = std::string(route_path) + "/topology/trajectories";
    logger.log_info("Check trajectories at directory \"%s\"", path.c_str());

    std::vector<std::string> trajectory_names;
    for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator(path))
    {
        if (file.path().extension() == ".traj")
        {
            logger.log_info("Found trajectory \"%s\"", file.path().filename().c_str());
            trajectory_names.emplace_back(file.path().stem());
        }
    }

    return trajectory_names;
}

std::vector<std::vector<ModuleDescriptor>> Topology::load_topology_configs(std::string_view route_path)
{
    // TODO:
    return {};
}
