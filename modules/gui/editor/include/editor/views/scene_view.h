#ifndef PROJECT_SCENE_VIEW_H
#define PROJECT_SCENE_VIEW_H

#include <editor/view.h>

#include <memory>
#include <vector>

namespace ifx {

class SceneContainer;
class RenderObject;
class GameObject;
class GameComponent;

class GameObjectView;
class GameComponentView;
class SceneManipulatorView;
class SceneManipulator;
class ResourceContext;

class GameObjectContextMenu;
class GameComponentContextMenu;
class SceneListContextMenu;

class SceneView : public View {
public:

    SceneView(std::shared_ptr<SceneContainer> scene,
              std::shared_ptr<ResourceContext> resource_creator);
    ~SceneView();

    std::shared_ptr<SceneManipulator> scene_manipulator(){
        return scene_manipulator_;}

    void SetSelectedGameObject(std::shared_ptr<GameObject> game_object){
        selected_game_object_ = game_object;}

protected:
    virtual void RenderContent() override;

private:
    void RenderWindow();

    void RenderGameObjectsList();

    void RenderSelectedGameObject();
    void RenderSelectedGameComponent();
    void RenderManipulator();

    void RenderGameObjectsList(
            std::vector<std::shared_ptr<GameObject>>& game_objects);

    void RenderGameComponentsList(std::shared_ptr<GameObject> game_object,
                                  int game_object_id);

    std::string GetComponentName(std::shared_ptr<GameComponent> game_component,
                                 int game_object_id,
                                 int component_id);

    std::shared_ptr<SceneContainer> scene_;
    std::shared_ptr<SceneManipulator> scene_manipulator_;

    std::shared_ptr<GameObject> selected_game_object_;
    std::shared_ptr<GameComponent> selected_game_component_;

    std::unique_ptr<GameObjectView> game_object_view_;
    std::unique_ptr<GameComponentView> game_component_view_;
    std::unique_ptr<SceneManipulatorView> scene_manipulator_view_;

    std::unique_ptr<GameObjectContextMenu> game_object_context_menu_;
    std::unique_ptr<GameComponentContextMenu> game_component_context_menu_;
    std::unique_ptr<SceneListContextMenu> scene_list_context_menu_;

    std::shared_ptr<ResourceContext> resource_creator_;
};
}

#endif //PROJECT_SCENE_VIEW_H
