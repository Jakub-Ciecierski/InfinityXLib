#ifndef PROJECT_GAME_OBJECT_CONTEXT_MENU_H
#define PROJECT_GAME_OBJECT_CONTEXT_MENU_H

#include <memory>

namespace ifx {

class GameObject;
class SceneContainer;
class ResourceContext;
class ContextMenuAddRenderObject;
class ContextMenuAddLight;
class SceneRenderer;

enum class GameObjectContextMenuEvent{
    Remove, Add, None
};

class GameObjectContextMenu {
public:
    GameObjectContextMenu(std::shared_ptr<SceneRenderer> scene_renderer,
                          std::shared_ptr<ResourceContext> resource_creator,
                          std::shared_ptr<SceneContainer> scene);
    ~GameObjectContextMenu() = default;

    GameObjectContextMenuEvent Render(std::shared_ptr<GameObject> game_object,
                                      int game_object_id);

private:

    bool Remove(std::shared_ptr<SceneContainer> scene,
                std::shared_ptr<GameObject> game_object);

    void Add(std::shared_ptr<SceneRenderer> scene_renderer,
             std::shared_ptr<ResourceContext> resource_creator,
             std::shared_ptr<GameObject> game_object);

    void AddLight(std::shared_ptr<ResourceContext> resource_creator,
                  std::shared_ptr<GameObject> game_object);

    void AddRenderObject(
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<ResourceContext> resource_creator,
            std::shared_ptr<GameObject> game_object);


    std::unique_ptr<ContextMenuAddLight> context_menu_add_light_;
    std::unique_ptr<ContextMenuAddRenderObject> context_menu_add_render_object_;

    std::shared_ptr<SceneRenderer> scene_renderer_;
    std::shared_ptr<ResourceContext> resource_creator_;
    std::shared_ptr<SceneContainer> scene_;
};
}

#endif //PROJECT_GAME_OBJECT_CONTEXT_MENU_H
