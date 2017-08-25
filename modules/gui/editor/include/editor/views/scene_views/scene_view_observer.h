#ifndef PROJECT_SCENE_VIEW_OBSERVER_H
#define PROJECT_SCENE_VIEW_OBSERVER_H

#include <memory>

namespace ifx {

class GameObject;

class SceneViewObserver {
public:
    SceneViewObserver() = default;
    virtual ~SceneViewObserver() = default;

    virtual void OnSetSelectedGameObject(
            std::shared_ptr<GameObject> selected_game_object) = 0;
};
}

#endif //PROJECT_SCENE_VIEW_OBSERVER_H
