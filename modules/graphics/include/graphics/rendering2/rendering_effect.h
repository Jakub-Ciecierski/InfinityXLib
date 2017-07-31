#ifndef PROJECT_RENDERING_EFFECT_H
#define PROJECT_RENDERING_EFFECT_H

#include <memory>
#include <vector>

namespace ifx {

class Program;
class RenderingState;
class RenderObject;
class Camera;
class LightGroup;

class RenderingEffect {
public:

    RenderingEffect(std::shared_ptr<Program> program,
                    std::shared_ptr<RenderingState> rendering_state);

    ~RenderingEffect();

    void Render(Camera &camera,
                LightGroup &light_source);

    void RegisterRenderObject(std::shared_ptr<RenderObject> render_object);
    bool DeregisterRenderObject(std::shared_ptr<RenderObject> render_object);

private:
    std::shared_ptr<Program> program_;
    std::shared_ptr<RenderingState> rendering_state_;

    std::vector<std::shared_ptr<RenderObject>> render_objects_;
};
}


#endif //PROJECT_RENDERING_EFFECT_H
