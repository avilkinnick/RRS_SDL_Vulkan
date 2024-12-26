#ifndef SIMULATOR_TOPOLOGY_MODULE_DESCRIPTOR_H
#define SIMULATOR_TOPOLOGY_MODULE_DESCRIPTOR_H

#include <string>
#include <vector>

struct ModuleDescriptor
{
    std::string name;
    std::vector<std::string> trajectory_names;
};

#endif // SIMULATOR_TOPOLOGY_MODULE_DESCRIPTOR_H
