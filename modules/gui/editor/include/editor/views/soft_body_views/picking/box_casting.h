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

    float Area() const {
        auto a = glm::length(a_start - c_interpolated);
        auto b = glm::length(c_interpolated - d_end);
        return a * b;
    }

    bool IsInside(const glm::vec2& viewport_point) const {
        if(a_start.x < d_end.x
            && a_start.y < d_end.y){
            if(viewport_point.x > a_start.x
                && viewport_point.x < d_end.x
                && viewport_point.y > a_start.y
                && viewport_point.y < d_end.y){
                return true;
            }
        }

        if(a_start.x > d_end.x
            && a_start.y < d_end.y){
            if(viewport_point.x < a_start.x
                && viewport_point.x > d_end.x
                && viewport_point.y > a_start.y
                && viewport_point.y < d_end.y){
                return true;
            }
        }

        if(a_start.x < d_end.x
            && a_start.y > d_end.y){
            if(viewport_point.x > a_start.x
                && viewport_point.x < d_end.x
                && viewport_point.y < a_start.y
                && viewport_point.y > d_end.y){
                return true;
            }
        }

        if(a_start.x > d_end.x
            && a_start.y > d_end.y){
            if(viewport_point.x < a_start.x
                && viewport_point.x > d_end.x
                && viewport_point.y < a_start.y
                && viewport_point.y > d_end.y){
                return true;
            }
        }

        return false;
    }
};

class BoxCasting {
public:
    BoxCasting(std::shared_ptr<RenderComponent> render_component);
    ~BoxCasting() = default;

    void window_width(int width){ window_width_ = width; }
    void window_height(int height) {window_height_ = height;}

    void projection(const glm::mat4& projection) {projection_ = projection;}
    void view(const glm::mat4& view) {view_ = view;}

    const BoxViewport& box_viewport(){return box_viewport_;}

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
