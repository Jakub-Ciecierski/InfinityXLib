#ifndef PROJECT_SCENE_MANIPULATOR_VIEW_H
#define PROJECT_SCENE_MANIPULATOR_VIEW_H

#include <memory>
#include <editor/view.h>
#include <editor/scene_manipulator.h>

namespace ifx {

class Transformable;
class CameraComponent;

/**
 * Responsible for controling the scene manipulator
 */
class SceneManipulatorView {
public:

    SceneManipulatorView(std::shared_ptr<SceneManipulator> scene_manipulator);
    ~SceneManipulatorView();

    void Render(std::shared_ptr<Transformable> object,
                std::shared_ptr<CameraComponent> camera);
private:
    void RenderConfig();

    std::shared_ptr<SceneManipulator> scene_manipulator_;

    SceneManipulatorOperation current_operation_;

    bool render_;
};
}

#endif //PROJECT_SCENE_MANIPULATOR_VIEW_H
