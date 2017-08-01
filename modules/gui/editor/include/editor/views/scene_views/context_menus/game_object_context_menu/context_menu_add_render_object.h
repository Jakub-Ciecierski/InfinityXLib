#ifndef PROJECT_GAME_OBJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_H
#define PROJECT_GAME_OBJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_H

#include <memory>
#include <string>


namespace ifx {

class ResourceContext;
class GameObject;
class ParametricEquationExpressions;
class ContextMenuAddRenderObjectParametricEquation;
class SceneRenderer;

class ContextMenuAddRenderObject {
public:

    ContextMenuAddRenderObject();

    ~ContextMenuAddRenderObject();

    void Render(
            std::shared_ptr<SceneRenderer> scene_renderer,
            std::shared_ptr<ResourceContext> resource_creator,
            std::shared_ptr<GameObject> game_object);
private:
    std::unique_ptr<ContextMenuAddRenderObjectParametricEquation>
            context_menu_add_render_object_parametric_equation_;
};
}


#endif //PROJECT_GAME_OBJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_H
