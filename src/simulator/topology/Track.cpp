#include "simulator/topology/Track.h"

#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_double3.hpp>

Track::Track(const glm::dvec3& point1, const glm::dvec3& point2)
{
    begin_point = point1;
    end_point = point2;

    glm::dvec3 difference = point2 - point1;

    length = glm::length(difference);
    orth = glm::normalize(difference);
    inclination = orth.z * 1000.0; // TODO: What the 1000.0?

    trav.x = difference.y;
    trav.y = -difference.x;
    trav.z = 0.0;
    trav = glm::normalize(trav);

    up = glm::cross(trav, difference);
    up = glm::normalize(up);
}
