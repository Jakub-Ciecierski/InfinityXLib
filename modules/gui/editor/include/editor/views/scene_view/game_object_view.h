#ifndef PROJECT_GAME_OBJECT_VIEW_H
#define PROJECT_GAME_OBJECT_VIEW_H

#include <memory>

namespace ifx {

class MovableObjectView;
class GameObject;

class GameObjectView {
public:

    GameObjectView();
    ~GameObjectView();

    void Render(std::shared_ptr<GameObject> game_object);
private:
    void RenderRemove(std::shared_ptr<GameObject> game_object);

    std::unique_ptr<MovableObjectView> movable_object_view_;
};
}

#endif //PROJECT_GAME_OBJECT_VIEW_H
