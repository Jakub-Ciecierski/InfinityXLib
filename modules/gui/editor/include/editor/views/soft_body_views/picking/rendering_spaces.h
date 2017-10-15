#ifndef PROJECT_RENDERING_SPACES_H
#define PROJECT_RENDERING_SPACES_H

#include <math/math_ifx.h>

namespace ifx {

extern const float z_forward;

glm::vec3 ViewPortSpace2NormalisedDeviceSpace(
    const glm::vec2& viewport_space,
    int window_width, int window_height);
glm::vec4 NormalisedDeviceSpace2HomogeneousClipSpace(
    const glm::vec3& nds);
glm::vec4 HomogeneousClipSpace2EyeSpace(const glm::vec4& clip_space,
                                        const glm::mat4& projection);
glm::vec3 EyeSpace2WorldSpace(const glm::vec4& eye_space,
                              const glm::mat4& view);

}

#endif //PROJECT_RENDERING_SPACES_H
