#ifndef PROJECT_SCENE_LIST_CONTEXT_MENU_H
#define PROJECT_SCENE_LIST_CONTEXT_MENU_H

#include <memory>

namespace ifx {

class SceneContainer;

class SceneListContextMenu {
public:
    SceneListContextMenu(std::shared_ptr<SceneContainer> scene);
    ~SceneListContextMenu();

    void Render();
private:
    std::shared_ptr<SceneContainer> scene_;
};

}

#endif //PROJECT_SCENE_LIST_CONTEXT_MENU_H
