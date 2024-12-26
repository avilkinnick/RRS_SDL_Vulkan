#ifndef SIMULATOR_TOPOLOGY_TOPOLOGY_H
#define SIMULATOR_TOPOLOGY_TOPOLOGY_H

#include <string_view>

class Topology
{
public:
    void load(std::string_view route_directory);
};

#endif // SIMULATOR_TOPOLOGY_TOPOLOGY_H
