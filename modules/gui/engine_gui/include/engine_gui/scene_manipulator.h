#ifndef PROJECT_SCENE_MANIPULATOR_H
#define PROJECT_SCENE_MANIPULATOR_H

#include <gui/guizmo/ImGuizmo.h>
#include <memory>

namespace ifx {

class MovableObject;
class Camera;

enum class SceneManipulatorOperation{
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

    void Manipulate(std::shared_ptr<MovableObject> movable_object,
                    std::shared_ptr<Camera> camera,
                    SceneManipulatorOperation operation);
private:
    void Manipulate(std::shared_ptr<MovableObject> movable_object,
                    const float* new_model_matrix,
                    SceneManipulatorOperation operation);

    ImGuizmo::OPERATION GetNativeOperationMode(
            SceneManipulatorOperation operation);

};
}

#endif //PROJECT_SCENE_MANIPULATOR_H
