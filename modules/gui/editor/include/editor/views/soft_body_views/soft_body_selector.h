#ifndef PROJECT_SOFT_BODY_SELECTOR_H
#define PROJECT_SOFT_BODY_SELECTOR_H

#include <memory>

namespace ifx {

class GameObject;
class RenderComponent;
class SceneContainer;

struct SoftBodyRenderingEffects;
struct SoftBodyObjects;

class SoftBodySelector {
public:
    SoftBodySelector(std::shared_ptr<SceneContainer> scene);

    ~SoftBodySelector() = default;

    void Select(std::shared_ptr<GameObject> selected_game_object,
                SoftBodyRenderingEffects& rendering_effects,
                SoftBodyObjects& soft_body_objects);
private:
    void RemoveCurrentGameObject(SoftBodyObjects& soft_body_objects);
    bool CheckSelectedGameObjectCorrectness(
            std::shared_ptr<GameObject> selected_game_object,
            SoftBodyObjects& soft_body_objects);
    SoftBodyObjects CreateNewGameObject(
            std::shared_ptr<GameObject> selected_game_object,
            SoftBodyRenderingEffects& rendering_effects);
    void RegisterGameObjectToRenderingEffects(
            std::shared_ptr<RenderComponent> render_component,
            SoftBodyRenderingEffects& rendering_effects);

    std::shared_ptr<SceneContainer> scene_;
};

}

#endif //PROJECT_SOFT_BODY_SELECTOR_H
