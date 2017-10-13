#include <iostream>
#include <math/print_math.h>
#include "editor/views/soft_body_views/picking/ray_casting.h"

namespace ifx {

RayCasting::RayCasting() :
    window_width_(0),
    window_height_(0),
    projection_(glm::mat4()),
    view_(glm::mat4()),
    origin_(glm::vec3()){}

Ray RayCasting::ComputeRayDirection(const glm::vec2 &viewport_space){
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

glm::vec3 RayCasting::ViewPortSpace2NormalisedDeviceSpace(
    const glm::vec2& viewport_space,
    int window_width, int window_height){
    // assume [0; width], [0; height]
    auto nds = glm::vec3(
        (2.0f * viewport_space.x) / window_width - 1.0f,
        (2.0f * viewport_space.y) / window_height - 1.0f,
        1.0f
    );

    //ifx::PrintVec3(nds);

    return nds;
}

glm::vec4 RayCasting::NormalisedDeviceSpace2HomogeneousClipSpace(
    const glm::vec3& nds){
    return glm::vec4(nds.x,
                     nds.y,
                     z_forward_,
                     1);
}

glm::vec4 RayCasting::HomogeneousClipSpace2EyeSpace(
    const glm::vec4 &clip_space,
    const glm::mat4 &projection){
    auto eye_space = glm::inverse(projection) * clip_space;
    auto eye = glm::vec4(eye_space.x,
                     eye_space.y,
                     z_forward_,
                     0);
    //ifx::PrintVec4(eye);
    return eye;
}

glm::vec3 RayCasting::EyeSpace2WorldSpace(const glm::vec4 &eye_space,
                                          const glm::mat4 &view){
    auto world4 = glm::inverse(view) * eye_space;
    auto world = glm::normalize(glm::vec3(world4.x, world4.y, world4.z));

    return world;
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

}