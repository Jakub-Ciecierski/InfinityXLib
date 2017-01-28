#ifndef PROJECT_SCENE_VIEW_H
#define PROJECT_SCENE_VIEW_H

#include <engine_gui/view.h>

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

class SceneView : public View {
public:

    SceneView(std::shared_ptr<SceneContainer> scene);
    ~SceneView();

    void SetSelectedGameObject(
            std::shared_ptr<GameObject> selected_game_object){
        selected_game_object_ = selected_game_object;
    }

    void Render() override;

private:
    void RenderWindow();
    void RenderGameObjectsList(
            std::vector<std::shared_ptr<GameObject>>& game_objects);
    void RenderGameComponentsList(std::shared_ptr<GameObject> game_object,
                                  int game_object_id);

    std::string GetComponentName(std::shared_ptr<GameComponent> game_component,
                                 int game_object_id,
                                 int component_id);

    std::shared_ptr<SceneContainer> scene_;

    std::shared_ptr<GameObject> selected_game_object_;
    std::shared_ptr<GameComponent> selected_game_component_;

    std::unique_ptr<GameObjectView> game_object_view_;
    std::unique_ptr<GameComponentView> game_component_view_;
    std::unique_ptr<SceneManipulatorView> scene_manipulator_view_;
};
}

#endif //PROJECT_SCENE_VIEW_H
