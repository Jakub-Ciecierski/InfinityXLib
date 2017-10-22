#include "editor/views/soft_body_views/picking/ray_casting.h"

#include "editor/views/soft_body_views/picking/rendering_spaces.h"

#include <iostream>
#include <math/print_math.h>

namespace ifx {

RayCasting::RayCasting() :
    window_width_(0),
    window_height_(0),
    projection_(glm::mat4()),
    view_(glm::mat4()),
    origin_(glm::vec3()){}

Ray RayCasting::ComputeRay(const glm::vec2 &viewport_space){
    auto nds = ViewPortSpace2NormalisedDeviceSpace(
        viewport_space,
        window_width_, window_height_);
    auto clip_space = NormalisedDeviceSpace2HomogeneousClipSpace(nds);
    auto eye_space = HomogeneousClipSpace2EyeSpace(clip_space,
                                                   projection_);
    auto world_space = EyeSpace2WorldSpace(eye_space,
                                           view_);
    return Ray{origin_, world_space};
}

SphereRayIntersectionOutput RayCasting::RaySphereIntersection(
    const Ray &ray, const Sphere &sphere) {
    auto radius_sqr = sphere.radius * sphere.radius;
    auto L = ray.origin - sphere.center;

    auto a = 1.0f;
    auto b = 2.0f * glm::dot(ray.direction, L);
    auto c = glm::dot(L, L) - radius_sqr;

    return ComputeQuadratic(a, b, c);
}

SphereRayIntersectionOutput RayCasting::ComputeQuadratic(
    float a, float b, float c){
    auto b_sqr = b * b;
    auto a_2 = 2.0f * a;
    auto delta = b_sqr - 4*a*c;

    if(delta == 0){
        float t = -b / (a_2);
        return SphereRayIntersectionOutput{1, t, -1};
    }
    else if(delta > 0){
        auto delta_sqrt = sqrt(delta);
        float t1 = (-b + delta_sqrt) / a_2;
        float t2 = (-b - delta_sqrt) / a_2;

        return SphereRayIntersectionOutput{2, t1, t2};
    }

    return SphereRayIntersectionOutput{0, -1, -1};
}

TriangleRayIntersectionOutput RayCasting::TriangleRayIntersection(
    const Ray& ray,
    const Triangle& triangle){
    TriangleRayIntersectionOutput output;
    output.is_intersection = false;

    const float EPSILON = 0.0000001;
    auto vertex0 = triangle.v1;
    auto vertex1 = triangle.v2;
    auto vertex2 = triangle.v3;

    auto edge1 = vertex1 - vertex0;
    auto edge2 = vertex2 - vertex0;
    auto h = glm::cross(ray.direction, edge2);
    auto a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON){
        return output;
    }

    auto f = 1.0f / a;
    auto s = ray.origin - vertex0;
    auto u = f * (glm::dot(s,h));
    if (u < 0.0 || u > 1.0){
        return output;
    }

    auto q = glm::cross(s, edge1);
    auto v = f * glm::dot(ray.direction, q);
    if (v < 0.0 || u + v > 1.0){
        return output;
    }

    auto t = f * glm::dot(edge2, q);
    if (t > EPSILON) // ray intersection
    {
        output.intersection_point = ray.origin + (
            ray.direction * (t * glm::length(ray.direction)));
        output.is_intersection = true;
        return output;
    }
    else{
        return output;
    }
}

}