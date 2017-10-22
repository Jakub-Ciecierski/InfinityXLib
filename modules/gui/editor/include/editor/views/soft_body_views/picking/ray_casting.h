#ifndef PROJECT_RAY_CASTING_H
#define PROJECT_RAY_CASTING_H

#include <math/math_ifx.h>

namespace ifx {

struct Ray{
    glm::vec3 origin;
    glm::vec3 direction;
};

struct Sphere{
    glm::vec3 center;
    float radius;
};

struct SphereRayIntersectionOutput{
    int number_of_solutions;
    float t1;
    float t2;
};


struct Triangle{
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
};


struct TriangleRayIntersectionOutput{
    bool is_intersection;
    glm::vec3 intersection_point;
};

class RayCasting {
public:
    RayCasting();
    ~RayCasting() = default;

    void window_width(int width){ window_width_ = width; }
    void window_height(int height) {window_height_ = height;}

    void projection(const glm::mat4& projection) {projection_ = projection;}
    void view(const glm::mat4& view) {view_ = view;}

    void origin(const glm::vec3& origin){origin_ = origin;}

    Ray ComputeRay(const glm::vec2 &viewport_space);

    SphereRayIntersectionOutput RaySphereIntersection(const Ray& ray,
                                                      const Sphere& sphere);

    TriangleRayIntersectionOutput TriangleRayIntersection(
        const Ray& ray,
        const Triangle& triangle);
private:
    SphereRayIntersectionOutput ComputeQuadratic(float a, float b, float c);

    int window_width_;
    int window_height_;

    glm::mat4 projection_;
    glm::mat4 view_;

    glm::vec3 origin_;
};

}

#endif //PROJECT_RAY_CASTING_H
