#ifndef PROJECT_GAME_OBJECT_VIEW_H
#define PROJECT_GAME_OBJECT_VIEW_H

#include <memory>

namespace ifx {

class GameObject;

class GameObjectView {
public:

    GameObjectView();
    ~GameObjectView();

    void Render(std::shared_ptr<GameObject> game_object);
private:
};
}

#endif //PROJECT_GAME_OBJECT_VIEW_H
