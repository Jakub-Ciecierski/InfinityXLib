#ifndef PROJECT_SOFT_BODY_VIEW_H
#define PROJECT_SOFT_BODY_VIEW_H

#include <memory>

#include <editor/view.h>
#include <editor/views/scene_views/scene_view_observer.h>

namespace ifx {

class GameUpdater;
class GameObject;
class RenderingEffect;
class RenderComponent;

struct SoftBodyRenderingEffects{
    std::shared_ptr<RenderingEffect> nodes = nullptr;
    std::shared_ptr<RenderingEffect> edges = nullptr;
    std::shared_ptr<RenderingEffect> faces = nullptr;
    std::shared_ptr<RenderingEffect> main = nullptr;
};

struct SoftBodyObjects{
    std::shared_ptr<GameObject> current_game_object;
    std::shared_ptr<RenderComponent> triangle_mesh;
    std::shared_ptr<RenderComponent> fem_geometry;
};

class SoftBodyView : public View, public SceneViewObserver {
public:
    SoftBodyView(std::unique_ptr<GameUpdater> game_updater,
                 const SoftBodyRenderingEffects& rendering_effects);
    ~SoftBodyView() = default;

    bool Terminate() override;

    virtual void Render() override;

    void SetGameObject(std::shared_ptr<GameObject> current_game_object);

    void OnSetSelectedGameObject(
            std::shared_ptr<GameObject> selected_game_object) override;

private:
    void RenderSettings();
    void RenderShow();
    void RenderShowRenderingEffects();
    void RenderShowRenderingEffectCheckbox(std::string name,
                                           RenderingEffect &rendering_effect);
    void RenderShowObjects();
    void RenderShowObjectCheckbox(std::string name,
                                  RenderComponent& render_component);
    void RenderMeshingButton();

    void RenderScreen();

    void RemoveCurrentGameObject();
    bool CheckSelectedGameObjectCorrectness(
            std::shared_ptr<GameObject> selected_game_object);
    SoftBodyObjects CreateNewGameObject(
            std::shared_ptr<GameObject> selected_game_object);
    void RegisterGameObjectToRenderingEffects(
            std::shared_ptr<RenderComponent> current_game_object_);

    std::unique_ptr<GameUpdater> game_updater_;

    SoftBodyRenderingEffects rendering_effects_;
    SoftBodyObjects soft_body_objects_;

    bool first_render_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_H
