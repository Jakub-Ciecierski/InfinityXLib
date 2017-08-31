#ifndef PROJECT_SOFT_BODY_VIEW_H
#define PROJECT_SOFT_BODY_VIEW_H

#include <memory>

#include <editor/view.h>
#include <editor/views/scene_views/scene_view_observer.h>
#include <editor/views/soft_body_views/soft_body_structers.h>

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>

namespace ifx {

class GameUpdater;
class GameObject;
class RenderingEffect;
class RenderComponent;

class SoftBodyScreenView;
class SoftBodySettingsView;
class SoftBodyCreatorView;
class SoftBodySelector;

class SoftBodyView : public View, public SceneViewObserver {
public:
    SoftBodyView(std::unique_ptr<GameUpdater> game_updater,
                 const SoftBodyRenderingEffects& rendering_effects);
    ~SoftBodyView() = default;

    bool Terminate() override;

    virtual void Render() override;

    void OnSetSelectedGameObject(
            std::shared_ptr<GameObject> selected_game_object) override;

private:
    void RenderLeftColumn();
    void RenderRightColumn();

    std::unique_ptr<GameUpdater> game_updater_;

    SoftBodyRenderingEffects rendering_effects_;
    SoftBodyObjects soft_body_objects_;

    bool first_render_;

    std::unique_ptr<SoftBodyScreenView> screen_view_;
    std::unique_ptr<SoftBodySettingsView> settings_view_;
    std::unique_ptr<SoftBodyCreatorView> creator_view_;
    std::unique_ptr<SoftBodySelector> selector_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_H
