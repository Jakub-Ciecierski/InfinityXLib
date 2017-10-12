#ifndef PROJECT_SOFT_BODY_STRUCTERS_H
#define PROJECT_SOFT_BODY_STRUCTERS_H

#include <memory>

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
};

struct SoftBodyObjects {
    std::shared_ptr<GameObject> current_game_object;
    std::shared_ptr<RenderComponent> triangle_mesh;
    std::shared_ptr<RenderComponent> soft_body_fem_render;
    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body_fem;
};

extern const unsigned int MAX_RENDER_COMPONENTS;

}

#endif //PROJECT_SOFT_BODY_STRUCTERS_H
