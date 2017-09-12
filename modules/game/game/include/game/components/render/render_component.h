#ifndef PROJECT_RENDERCOMPONENT_H
#define PROJECT_RENDERCOMPONENT_H

#include <game/game_component.h>
#include <graphics/rendering/render_object.h>

namespace ifx {

class RenderComponent : public GameComponent, public RenderObject {
public:
    RenderComponent(std::shared_ptr<Model>);
    RenderComponent(std::vector<std::shared_ptr<Model>>);

    ~RenderComponent() = default;

private:
};
}

#endif //PROJECT_RENDERCOMPONENT_H
