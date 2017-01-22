#ifndef PROJECT_GAME_OBJECT_VIEW_H
#define PROJECT_GAME_OBJECT_VIEW_H

#include <memory>

namespace ifx {

class MovableObjectView;
class GameObject;
class SceneContainer;

class GameObjectView {
public:

    GameObjectView();
    ~GameObjectView();

    void Render(std::shared_ptr<GameObject> game_object,
                std::shared_ptr<SceneContainer> scene);
private:
    void RenderRemove(std::shared_ptr<GameObject> game_object,
                      std::shared_ptr<SceneContainer> scene);

    std::unique_ptr<MovableObjectView> movable_object_view_;
};
}

#endif //PROJECT_GAME_OBJECT_VIEW_H
