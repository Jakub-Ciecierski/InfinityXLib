#include "editor/views/soft_body_views/picking/ray_casting.h"

namespace ifx {

RayCasting::RayCasting() :
    window_width_(0),
    window_height_(0),
    projection_(glm::mat4()),
    view_(glm::mat4()){}

void RayCasting::ComputeRay(const glm::vec2& viewport_space){
    auto nds = ViewPortSpace2NormalisedDeviceSpace(
        viewport_space,
        window_width_, window_height_);
    auto clip_space = NormalisedDeviceSpace2HomogeneousClipSpace(nds);
    auto eye_space = HomogeneousClipSpace2EyeSpace(clip_space,
                                                   projection_);
    auto world_space = EyeSpace2WorldSpace(eye_space,
                                           view_);
}

glm::vec3 RayCasting::ViewPortSpace2NormalisedDeviceSpace(
    const glm::vec2& viewport_space,
    int window_width, int window_height){
    // assume [0; width], [height; 0]
    return glm::vec3(
        (2.0f * viewport_space.x) / window_width - 1.0f,
        1.0f - (2.0f * viewport_space.y) / window_height,
        1.0f
    );
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
    return glm::vec4(eye_space.x,
                     eye_space.y,
                     z_forward_,
                     0);
}

glm::vec3 RayCasting::EyeSpace2WorldSpace(const glm::vec4 &eye_space,
                                          const glm::mat4 &view){
    auto world4 = glm::inverse(view) * eye_space;
    auto world = glm::normalize(glm::vec3(world4.x, world4.y, world4.z));
    return world;
}

}