#ifndef PROJECT_SCENE_VIEW_SUBJECT_H
#define PROJECT_SCENE_VIEW_SUBJECT_H

#include <memory>
#include <vector>

namespace ifx {

class GameObject;
class SceneViewObserver;

class SceneViewSubject {
public:
    SceneViewSubject() = default;
    virtual ~SceneViewSubject() = default;

    void AddObserver(std::shared_ptr<SceneViewObserver> observer);
    bool RemoveObserver(std::shared_ptr<SceneViewObserver> observer);

    void NotifySetSelectedGameObject(
            std::shared_ptr<GameObject> selected_game_object);

private:
    std::vector<std::weak_ptr<SceneViewObserver>> observers_;

};
}

#endif //PROJECT_SCENE_VIEW_SUBJECT_H
