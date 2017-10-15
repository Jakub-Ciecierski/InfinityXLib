#include "editor/views/soft_body_views/picking/rendering_spaces.h"

namespace ifx {

const float z_forward = -1;

glm::vec3 ViewPortSpace2NormalisedDeviceSpace(
    const glm::vec2& viewport_space,
    int window_width, int window_height){
    // assume [0; width], [0; height]
    auto nds = glm::vec3(
        (2.0f * viewport_space.x) / window_width - 1.0f,
        (2.0f * viewport_space.y) / window_height - 1.0f,
        1.0f
    );

    return nds;
}

glm::vec4 NormalisedDeviceSpace2HomogeneousClipSpace(
    const glm::vec3& nds){
    return glm::vec4(nds.x,
                     nds.y,
                     z_forward,
                     1);
}

glm::vec4 HomogeneousClipSpace2EyeSpace(
    const glm::vec4 &clip_space,
    const glm::mat4 &projection){
    auto eye_space = glm::inverse(projection) * clip_space;
    auto eye = glm::vec4(eye_space.x,
                         eye_space.y,
                         z_forward,
                         0);
    return eye;
}

glm::vec3 EyeSpace2WorldSpace(const glm::vec4 &eye_space,
                                          const glm::mat4 &view){
    auto world4 = glm::inverse(view) * eye_space;
    auto world = glm::normalize(glm::vec3(world4.x, world4.y, world4.z));

    return world;
}

}