#ifndef PROJECT_SOFT_BODY_STRUCTERS_H
#define PROJECT_SOFT_BODY_STRUCTERS_H

#include <memory>

#include <game/components/physics/builder/soft_body_fem_component_builder.h>

namespace ifx {

class RenderingEffect;
class GameObject;
class RenderComponent;

template<class T>
class SoftBodyFEMComponent;

struct SoftBodyRenderingEffects {
    std::shared_ptr<RenderingEffect> nodes = nullptr;
    std::shared_ptr<RenderingEffect> edges = nullptr;
    std::shared_ptr<RenderingEffect> faces = nullptr;
    std::shared_ptr<RenderingEffect> main = nullptr;

    std::shared_ptr<RenderingEffect> axis = nullptr;

    void Register(std::shared_ptr<RenderComponent> render_component);
};

struct SoftBodyEditorObjects {
    SoftBodyEditorObjects();
    SoftBodyEditorObjects(
            std::shared_ptr<GameObject> current_game_object_,
            std::unique_ptr<SoftBodyFEMComponentBuilder<double>>
            soft_body_fem_component_builder_);

    std::shared_ptr<GameObject> current_game_object;

    std::unique_ptr<SoftBodyFEMComponentBuilder<double>>
        soft_body_fem_component_builder;

    std::shared_ptr<RenderComponent> current_fem_render_component;

    void UpdateFEMRenderComponent(
            std::shared_ptr<RenderComponent> render_component);
};

extern const unsigned int MAX_RENDER_COMPONENTS;

}

#endif //PROJECT_SOFT_BODY_STRUCTERS_H
