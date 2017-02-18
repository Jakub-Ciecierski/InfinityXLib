#ifndef PROJECT_SCENE_MANIPULATOR_VIEW_H
#define PROJECT_SCENE_MANIPULATOR_VIEW_H

#include <memory>
#include <engine_gui/view.h>
#include <engine_gui/scene_manipulator.h>

namespace ifx {

/**
 * Responsible for controling the scene manipulator
 */
class SceneManipulatorView {
public:

    SceneManipulatorView(std::shared_ptr<SceneManipulator> scene_manipulator);
    ~SceneManipulatorView();

    void Render();
private:
    void RenderConfig();

    std::shared_ptr<SceneManipulator> scene_manipulator_;

    SceneManipulatorOperation current_operation_;

    bool render_;
};
}

#endif //PROJECT_SCENE_MANIPULATOR_VIEW_H