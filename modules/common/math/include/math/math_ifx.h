#ifndef PROJECT_MATH_H
#define PROJECT_MATH_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

namespace ifx{

struct Dimensions{
    int width;
    int height;
};

struct SphereIntersection{
    glm::vec3 center;
    float radius;
};

struct LineIntersection{
    glm::vec3 origin;
    glm::vec3 direction;
};

struct LineSphereIntersection{
    const float NO_SOLUTION = -9999.9F;
    float d1 = NO_SOLUTION;
    float d2 = NO_SOLUTION;
};

/**
 * https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
 */
LineSphereIntersection Intersection(const LineIntersection& line,
                                    const SphereIntersection& sphere);

float Magnitude(const glm::vec3& v1);

float EuclideanDistance(const glm::vec3& v1, const glm::vec3& v2);
float EuclideanDistance(const glm::vec2& v1, const glm::vec2& v2);

float dot(const glm::vec3& v1, const glm::vec3& v2);

std::vector<std::string> SplitString(std::string s,
                                     std::string delimiter);


}

#endif //PROJECT_MATH_H
