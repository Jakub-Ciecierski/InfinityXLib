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
    void RenderShowCheckbox(std::string name,
                            RenderingEffect& rendering_effect);

    void RenderScreen();

    void RegisterGameObjectToRenderingEffects(
            std::shared_ptr<RenderComponent> current_game_object_);

    std::unique_ptr<GameUpdater> game_updater_;

    std::shared_ptr<GameObject> current_game_object_;

    SoftBodyRenderingEffects rendering_effects_;

    bool first_render_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_H
