#ifndef PROJECT_SOFT_BODY_SELECTOR_H
#define PROJECT_SOFT_BODY_SELECTOR_H

#include <memory>

namespace ifx {

class GameObject;
class RenderComponent;
class SceneContainer;
class ResourceManager;

struct SoftBodyRenderingEffects;
struct SoftBodyEditorObjects;

class SoftBodySelector {
public:
    SoftBodySelector(std::shared_ptr<SceneContainer> scene,
                     std::shared_ptr<ResourceManager> resource_manager);

    ~SoftBodySelector() = default;

    void Select(std::shared_ptr<GameObject> selected_game_object,
                SoftBodyRenderingEffects &rendering_effects,
                SoftBodyEditorObjects &soft_body_objects);
private:
    void RemoveCurrentGameObject(SoftBodyEditorObjects &soft_body_objects);
    bool CheckSelectedGameObjectCorrectness(
        std::shared_ptr<GameObject> selected_game_object,
        SoftBodyEditorObjects &soft_body_objects);
    SoftBodyEditorObjects CreateNewGameObject(
        std::shared_ptr<GameObject> selected_game_object,
        SoftBodyRenderingEffects &rendering_effects);
    void RegisterGameObjectToRenderingEffects(
        std::shared_ptr<RenderComponent> render_component,
        SoftBodyRenderingEffects &rendering_effects);

    std::shared_ptr<SceneContainer> scene_;

    std::shared_ptr<ResourceManager> resource_manager_;
};

}

#endif //PROJECT_SOFT_BODY_SELECTOR_H
