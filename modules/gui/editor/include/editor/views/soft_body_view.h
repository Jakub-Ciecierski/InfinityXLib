#ifndef PROJECT_SOFT_BODY_VIEW_H
#define PROJECT_SOFT_BODY_VIEW_H

#include <memory>

#include <editor/view.h>
#include <editor/views/scene_views/scene_view_observer.h>

namespace ifx {

class GameUpdater;
class GameObject;

class SoftBodyView : public View, public SceneViewObserver {
public:
    SoftBodyView(std::unique_ptr<GameUpdater> game_updater);
    ~SoftBodyView() = default;

    bool Terminate() override;

    virtual void Render() override;

    void SetGameObject(std::shared_ptr<GameObject> current_game_object);

    void OnSetSelectedGameObject(
            std::shared_ptr<GameObject> selected_game_object) override;

private:
    void RenderScreen();

    std::unique_ptr<GameUpdater> game_updater_;

    std::shared_ptr<GameObject> current_game_object_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_H
