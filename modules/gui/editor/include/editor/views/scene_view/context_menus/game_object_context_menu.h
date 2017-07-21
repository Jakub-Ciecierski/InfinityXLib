#ifndef PROJECT_GAME_OBJECT_CONTEXT_MENU_H
#define PROJECT_GAME_OBJECT_CONTEXT_MENU_H

#include <memory>

namespace ifx {

class GameObject;
class SceneContainer;
class ResourceContext;

class GameObjectContextMenu {
public:
    GameObjectContextMenu(std::shared_ptr<ResourceContext> resource_creator,
                          std::shared_ptr<SceneContainer> scene);
    ~GameObjectContextMenu();

    void Render(std::shared_ptr<GameObject> game_object,
                int game_object_id);

private:

    void Remove(std::shared_ptr<SceneContainer> scene,
                std::shared_ptr<GameObject> game_object,
                int game_object_id);

    void Add(std::shared_ptr<ResourceContext> resource_creator,
             std::shared_ptr<GameObject> game_object,
             int game_object_id);

    void AddLight(std::shared_ptr<ResourceContext> resource_creator,
                  std::shared_ptr<GameObject> game_object,
                  int game_object_id);

    void AddRenderObject(std::shared_ptr<GameObject> game_object,
                         int game_object_id);

    std::shared_ptr<ResourceContext> resource_creator_;
    std::shared_ptr<SceneContainer> scene_;
};
}

#endif //PROJECT_GAME_OBJECT_CONTEXT_MENU_H
