#pragma once

#include <optional>
#include <string>
#include <vector>

struct CommandLineData
{
    std::optional<std::vector<std::string>> train_configs;
    std::optional<std::string> route_directory_name;
    bool clear_log;
    bool debug_print;
    std::optional<std::vector<double>> initial_coordinates;
    std::optional<std::vector<int>> directions;
    std::optional<std::vector<std::string>> trajectory_names;
};

