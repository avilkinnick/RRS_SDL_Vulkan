#pragma once

#include <glm/ext/vector_double3.hpp>

// TODO: Change names?
// TODO: Add serialize/deserialize?
class Track
{
public:
    Track() = default;
    Track(const glm::dvec3& point1, const glm::dvec3& point2);

public:
    glm::dvec3 begin_point = glm::dvec3(0.0);
    glm::dvec3 end_point = glm::dvec3(0.0);
    glm::dvec3 orth = glm::dvec3(0.0);
    glm::dvec3 trav = glm::dvec3(0.0);
    glm::dvec3 up = glm::dvec3(0.0);

    double length = 0.0;
    double inclination = 0.0;
    double curvature = 0.0;
    double trajectory_coordinate = 0.0;
    double railway_coordinate1 = 0.0;
    double railway_coordinate2 = 0.0;
};

