#include "graphics/rendering/rendering_effect.h"

#include "graphics/rendering/camera/camera.h"
#include "graphics/lighting/light_group.h"
#include <graphics/rendering/render_object.h>

namespace ifx {

RenderingEffect::RenderingEffect(
    std::shared_ptr<Program> program,
    const RenderingState &rendering_state,
    std::string name) :
    program_(program),
    rendering_state_(rendering_state),
    name_(name),
    enabled_(true) {}

RenderingEffect::RenderingEffect(const RenderingEffect &other) :
    program_(other.program_),
    rendering_state_(other.rendering_state_),
    name_(other.name_),
    enabled_(other.enabled_) {}

void RenderingEffect::Render(Camera &camera,
                             LightGroup &light_group) {
    if (!enabled_)
        return;
    camera.use(*program_);
    light_group.use(*program_);

    for (auto &render_object : render_objects_)
        render_object->Render(*program_);
}

void RenderingEffect::RegisterRenderObject(
    std::shared_ptr<RenderObject> render_object) {
    render_objects_.push_back(render_object);
    render_object->RegisterRenderingEffect(this);
}

bool RenderingEffect::DeregisterRenderObject(
    std::shared_ptr<RenderObject> render_object) {
    for (unsigned int i = 0; i < render_objects_.size(); i++) {
        if (render_objects_[i] == render_object) {
            render_objects_.erase(render_objects_.begin() + i);
            render_object->DeregisterRenderingEffect(this);
            return true;
        }
    }
    return false;
}

}