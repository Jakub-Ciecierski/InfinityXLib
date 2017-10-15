#ifndef PROJECT_BOX_CASTING_H
#define PROJECT_BOX_CASTING_H

#include <memory>

#include <math/math_ifx.h>

namespace ifx {

class RenderComponent;

struct BoxViewport {
    glm::vec2 a_start;
    glm::vec2 b_interpolated;
    glm::vec2 c_interpolated;
    glm::vec2 d_end;
};

class BoxCasting {
public:
    BoxCasting(std::shared_ptr<RenderComponent> render_component);
    ~BoxCasting() = default;

    void window_width(int width){ window_width_ = width; }
    void window_height(int height) {window_height_ = height;}

    void projection(const glm::mat4& projection) {projection_ = projection;}
    void view(const glm::mat4& view) {view_ = view;}

    void Begin(const glm::vec2& viewport_position);
    void Finish();

    void SetEndViewport(const glm::vec2& viewport_position);
private:
    void CalculateBoxPositions();
    void UpdateHomogeneousClipSpaceRenderingComponent();
    glm::vec4 ToHomogeneousClipSpace(const glm::vec2& a);

    std::shared_ptr<RenderComponent> box_render_component_;

    BoxViewport box_viewport_;

    int window_width_;
    int window_height_;

    glm::mat4 view_;
    glm::mat4 projection_;

};

}

#endif //PROJECT_BOX_CASTING_H
