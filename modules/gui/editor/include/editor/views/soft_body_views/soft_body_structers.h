#ifndef PROJECT_SOFT_BODY_STRUCTERS_H
#define PROJECT_SOFT_BODY_STRUCTERS_H

#include <memory>

namespace ifx {

class RenderingEffect;
class GameObject;
class RenderComponent;

struct SoftBodyRenderingEffects {
    std::shared_ptr<RenderingEffect> nodes = nullptr;
    std::shared_ptr<RenderingEffect> edges = nullptr;
    std::shared_ptr<RenderingEffect> faces = nullptr;
    std::shared_ptr<RenderingEffect> main = nullptr;
};

struct SoftBodyObjects {
    std::shared_ptr<GameObject> current_game_object;
    std::shared_ptr<RenderComponent> triangle_mesh;
    std::shared_ptr<RenderComponent> fem_geometry;
};

extern const unsigned int MAX_RENDER_COMPONENTS;

}

#endif //PROJECT_SOFT_BODY_STRUCTERS_H
