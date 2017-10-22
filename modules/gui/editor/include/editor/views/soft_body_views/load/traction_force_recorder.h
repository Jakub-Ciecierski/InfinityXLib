#ifndef PROJECT_TRACTION_FORCE_RECORDER_H
#define PROJECT_TRACTION_FORCE_RECORDER_H

#include <math/math_ifx.h>
#include <memory>

namespace ifx {

class RenderComponent;

class TractionForceRecorder {
public:
    TractionForceRecorder(std::shared_ptr<RenderComponent> render_component);
    ~TractionForceRecorder() = default;

    void Begin(const glm::vec2& viewport_position_begin);
    void Update(float window_width,
                float window_height,
                const glm::vec2& viewport_position);
    void End();

private:
    glm::vec4 ToHomogeneousClipSpace(const glm::vec2& a);

    std::shared_ptr<RenderComponent> render_component_;

    glm::vec2 viewport_position_begin_;
    glm::vec2 viewport_position_end_;

    float window_width_;
    float window_height_;
};

}

#endif //PROJECT_TRACTION_FORCE_RECORDER_H
