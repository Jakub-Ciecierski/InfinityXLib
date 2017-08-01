#ifndef PROJECT_RENDERING_EFFECT_H
#define PROJECT_RENDERING_EFFECT_H

#include <memory>
#include <vector>
#include "graphics/rendering/rendering_state.h"

namespace ifx {

class Program;
class RenderObject;
class Camera;
class LightGroup;

class RenderingEffect {
public:

    RenderingEffect(std::shared_ptr<Program> program,
                    const RenderingState &rendering_state,
                    std::string name = "Rendering Effect");

    ~RenderingEffect();

    std::shared_ptr<Program> program(){return program_;}
    const RenderingState& rendering_state(){return rendering_state_;}
    const std::string& name(){return name_;}

    void Render(Camera &camera,
                LightGroup &light_source);

    void RegisterRenderObject(std::shared_ptr<RenderObject> render_object);
    bool DeregisterRenderObject(std::shared_ptr<RenderObject> render_object);

private:
    std::shared_ptr<Program> program_;
    RenderingState rendering_state_;
    std::string name_;

    std::vector<std::shared_ptr<RenderObject>> render_objects_;
};
}


#endif //PROJECT_RENDERING_EFFECT_H
