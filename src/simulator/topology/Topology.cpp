#include "simulator/topology/Topology.h"

#include "ConfigFile.h"
#include "cmake_defines.h"
#include "Logger.h"
#include "simulator/topology/ModuleDescriptor.h"
#include "simulator/topology/Trajectory.h"

#include <algorithm>
#include <filesystem>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// TODO: Rename config/module?
void Topology::load(std::string_view route_directory_name)
{
    Logger& logger = Logger::get_instance();

    std::string route_path = std::string(ROUTES_DIR "/") + route_directory_name.data();

    std::vector<std::string> trajectory_names = get_trajectory_names(route_path);
    if (trajectory_names.empty())
    {
        throw std::runtime_error("Trajectories not found");
    }

    auto all_modules = load_topology_configs(route_path);
    for (std::string_view trajectory_name : trajectory_names)
    {
        std::unique_ptr<Trajectory> trajectory = std::make_unique<Trajectory>();

        std::vector<ModuleDescriptor> modules;
        for (const auto& all_configs : all_modules)
        {
            for (const ModuleDescriptor& module_config : all_configs)
            {
                const auto& trajectory_names = module_config.trajectory_names;
                auto found_it = std::find(trajectory_names.cbegin(), trajectory_names.cend(), trajectory_name);
                if (found_it != trajectory_names.cend())
                {
                    modules.emplace_back(module_config);
                    break;
                }
            }
        }

        trajectory->load(route_path, trajectory_name, modules);
    }
}

std::vector<std::string> Topology::get_trajectory_names(std::string_view route_path)
{
    Logger& logger = Logger::get_instance();

    std::string path = std::string(route_path) + "/topology/trajectories";
    logger.log_info("Check trajectories at directory \"%s\"", path.c_str());

    std::vector<std::string> trajectory_names;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".traj")
        {
            logger.log_info("Found trajectory \"%s\"", entry.path().filename().c_str());
            trajectory_names.emplace_back(entry.path().stem());
        }
    }

    return trajectory_names;
}

// TODO: Split on several functions
std::vector<std::vector<ModuleDescriptor>> Topology::load_topology_configs(std::string_view route_path)
{
    Logger& logger = Logger::get_instance();

    std::string topology_path = std::string(route_path) + "/topology";

    std::vector<std::vector<ModuleDescriptor>> all_modules;
    for (const std::filesystem::directory_entry& entry1 : std::filesystem::directory_iterator(topology_path))
    {
        constexpr const char* trajectory_directory_regex_string = R"(^trajectory-\w+)";
        std::regex trajectory_directory_regex(trajectory_directory_regex_string);
        if (entry1.is_directory() && std::regex_match(entry1.path().stem().c_str(), trajectory_directory_regex))
        {
            std::vector<ModuleDescriptor> all_configs;
            for (const std::filesystem::directory_entry& entry2 : std::filesystem::directory_iterator(entry1.path()))
            {
                if (entry2.path().extension() == ".xml")
                {
                    const auto& config_path = entry2.path();

                    ModuleDescriptor module_descriptor;
                    module_descriptor.name = config_path.stem();

                    ConfigFile config_file(config_path.c_str());
                    config_file.for_each("Trajectory", [&]() {
                        std::string trajectory_name = config_file.read<std::string>("Name");
                        if (trajectory_name.empty())
                        {
                            logger.log_warn("Empty trajectory name at \"%s\"", config_path.c_str());
                        }
                        else
                        {
                            module_descriptor.trajectory_names.emplace_back(trajectory_name);
                        }
                    });

                    if (module_descriptor.trajectory_names.empty())
                    {
                        logger.log_warn("No trajectories found in \"%s\"", config_path.c_str());
                    }
                    else
                    {
                        all_configs.emplace_back(std::move(module_descriptor));
                    }
                }
            }

            if (all_configs.empty())
            {
                logger.log_warn("No trajectories found in files at \"%s\"", entry1.path().c_str());
            }
            else
            {
                all_modules.emplace_back(std::move(all_configs));
            }
        }
    }

    return all_modules;
}
