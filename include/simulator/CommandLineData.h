#ifndef SIMULATOR_COMMAND_LINE_DATA_H
#define SIMULATOR_COMMAND_LINE_DATA_H

#include <optional>
#include <string_view>
#include <vector>

struct CommandLineData
{
    // TODO:
    std::optional<std::vector<std::string_view>> train_config;
    std::optional<std::string_view> route_dir;
    bool clear_log;
    bool debug_print;
    std::optional<std::vector<double>> init_coord;
    std::optional<std::vector<int>> direction;
    std::optional<std::vector<std::string_view>> trajectory_name;
};

#endif // SIMULATOR_COMMAND_LINE_DATA_H
