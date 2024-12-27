#include "simulator/topology/Trajectory.h"

#include "Logger.h"
#include "simulator/topology/ModuleDescriptor.h"
#include "simulator/topology/Track.h"

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
    Logger& logger = Logger::get_instance();

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

        Track track(point1, point2);
        track.railway_coordinate1 = railway_coordinate1;
        track.railway_coordinate2 = railway_coordinate2;
        track.trajectory_coordinate = length;
        length += track.length;
        tracks.emplace_back(std::move(track));
    }

    name = trajectory_name;

    if (modules.empty())
    {
        logger.log_warn("No modules for trajectory \"%s\"", trajectory_name);
    }
}
