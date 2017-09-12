#ifndef PROJECT_SCENE_MANIPULATOR_H
#define PROJECT_SCENE_MANIPULATOR_H

#include <gui/guizmo/ImGuizmo.h>
#include <memory>

namespace ifx {

class Transformable;
class CameraComponent;

enum class SceneManipulatorOperation {
    TRANSLATE, ROTATE, SCALE
};

/**
 * Scene Manipulator, translates, rotates and scales
 * selected objects in the scene
 */
class SceneManipulator {
public:

    SceneManipulator();
    ~SceneManipulator();

    void transformable_object(std::shared_ptr<Transformable> object) {
        transformable_object_ = object;
    };
    void camera(std::shared_ptr<CameraComponent> new_camera) {
        camera_ = new_camera;
    }
    void operation(SceneManipulatorOperation new_operation) {
        operation_ = new_operation;
    }

    bool show() { return show_; }
    void show(bool v) { show_ = v; }

    void Manipulate();

private:
    void Manipulate(std::shared_ptr<Transformable> movable_object,
                    const float *new_model_matrix,
                    SceneManipulatorOperation operation);

    ImGuizmo::OPERATION GetNativeOperationMode(
        SceneManipulatorOperation operation);

    std::shared_ptr<Transformable> transformable_object_;
    std::shared_ptr<CameraComponent> camera_;
    SceneManipulatorOperation operation_;

    bool show_;
};
}

#endif //PROJECT_SCENE_MANIPULATOR_H
