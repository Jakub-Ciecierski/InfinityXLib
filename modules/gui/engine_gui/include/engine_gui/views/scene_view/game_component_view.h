#ifndef PROJECT_GAME_COMPONENT_VIEW_H
#define PROJECT_GAME_COMPONENT_VIEW_H

#include <memory>

namespace ifx {

class GameComponent;
class MovableObjectView;
class CameraView;
class LightView;
class RenderObjectView;

class GameComponentView {
public:

    GameComponentView();
    ~GameComponentView();

    void Render(std::shared_ptr<GameComponent> game_component);

private:

    std::unique_ptr<MovableObjectView> movable_object_view_;

    std::unique_ptr<CameraView> camera_view_;
    std::unique_ptr<LightView> light_view_;
    std::unique_ptr<RenderObjectView> render_object_view_;
};
}

#endif //PROJECT_GAME_COMPONENT_VIEW_H
