#include "simulator/topology/Trajectory.h"

#include "simulator/topology/ModuleDescriptor.h"

#include <glm/ext/vector_double3.hpp>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

void Trajectory::load(
    std::string_view route_directory,
    std::string_view trajectory_name,
    std::vector<ModuleDescriptor> modules
)
{
    std::string path = std::string(route_directory) + "/topology/trajectories/" + trajectory_name.data() + ".traj";

    std::ifstream file(path);
    if (!file)
    {
        throw std::runtime_error(std::string("Path \"" + path +" \" not found"));
    }

    std::string track_begin_string;
    std::string track_end_string;
    while (std::getline(file, track_begin_string) && std::getline(file, track_end_string))
    {
        std::istringstream track_begin(track_begin_string);
        std::istringstream track_end(track_end_string);

        glm::dvec3 point1;
        double railway_coordinate1;
        track_begin >> point1.x >> point1.y >> point1.z >> railway_coordinate1;

        glm::dvec3 point2;
        double railway_coordinate2;
        track_end >> point2.x >> point2.y >> point2.z >> railway_coordinate2;
    }
}
