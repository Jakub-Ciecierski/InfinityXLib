#ifndef PROJECT_RAY_CASTING_H
#define PROJECT_RAY_CASTING_H

#include <math/math_ifx.h>

namespace ifx {

class RayCasting {
public:
    RayCasting();
    ~RayCasting() = default;

    void window_width(int width){ window_width_ = width; }
    void window_height(int height) {window_height_ = height;}

    void projection(const glm::mat4& projection) {projection_ = projection;}
    void view(const glm::mat4& view) {view_ = view;}

    void ComputeRay(const glm::vec2& viewport_space);
private:
    glm::vec3 ViewPortSpace2NormalisedDeviceSpace(
        const glm::vec2& viewport_space,
        int window_width, int window_height);
    glm::vec4 NormalisedDeviceSpace2HomogeneousClipSpace(
        const glm::vec3& nds);
    glm::vec4 HomogeneousClipSpace2EyeSpace(const glm::vec4& clip_space,
                                            const glm::mat4& projection);
    glm::vec3 EyeSpace2WorldSpace(const glm::vec4& eye_space,
                                  const glm::mat4& view);

    int window_width_;
    int window_height_;

    glm::mat4 projection_;
    glm::mat4 view_;

    const float z_forward_ = -1.0f;
};

}

#endif //PROJECT_RAY_CASTING_H
