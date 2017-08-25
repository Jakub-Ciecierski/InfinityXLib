#ifndef PROJECT_SCREEN_WINDOW_VIEW_H
#define PROJECT_SCREEN_WINDOW_VIEW_H

#include <editor/window_view.h>

namespace ifx {

class SceneView;
class SoftBodyView;

class ScreenWindowView : public WindowView {
public:
    ScreenWindowView(std::shared_ptr<SceneView> scene_screen_view,
                     std::shared_ptr<SoftBodyView> soft_body_view);
    ~ScreenWindowView() = default;

    virtual void Render() override;

private:
    std::shared_ptr<SceneView> scene_screen_view_;
    std::shared_ptr<SoftBodyView> soft_body_view_;
};

}

#endif //PROJECT_SCREEN_WINDOW_VIEW_H

