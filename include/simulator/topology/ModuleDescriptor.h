#pragma once

#include <string>
#include <vector>

struct ModuleDescriptor
{
    std::string name;
    std::vector<std::string> trajectory_names;
};
