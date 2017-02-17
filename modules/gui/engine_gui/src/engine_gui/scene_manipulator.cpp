#include "engine_gui/scene_manipulator.h"

#include <object/movable_object.h>
#include <graphics/rendering/camera/camera.h>
#include <math/print_math.h>

namespace ifx {

SceneManipulator::SceneManipulator() :
    movable_object_(nullptr),
    camera_(nullptr),
    operation_(SceneManipulatorOperation::TRANSLATE){
    ImGuizmo::Enable(true);
}

SceneManipulator::~SceneManipulator() { }

void SceneManipulator::Manipulate(std::shared_ptr<MovableObject> movable_object,
                                  std::shared_ptr<Camera> camera,
                                  SceneManipulatorOperation operation) {
    ImGuizmo::BeginFrame();

    const float *view = glm::value_ptr(camera->getViewMatrix());
    const float *projection = glm::value_ptr(camera->getProjectionMatrix());

    auto model = movable_object->GetModelMatrix();
    float *new_model_matrix = glm::value_ptr(model);

    ImGuizmo::Manipulate(view, projection,
                         GetNativeOperationMode(operation),
                         ImGuizmo::MODE::WORLD,
                         new_model_matrix);

    if (ImGuizmo::IsUsing())
        Manipulate(movable_object, new_model_matrix, operation);
}

void SceneManipulator::Manipulate() {
    if(!show_)
        return;
    if(!movable_object_ || !camera_)
        return;

    ImGuizmo::BeginFrame();

    const float *view = glm::value_ptr(camera_->getViewMatrix());
    const float *projection = glm::value_ptr(camera_->getProjectionMatrix());

    auto model = movable_object_->GetModelMatrix();
    float *new_model_matrix = glm::value_ptr(model);

    ImGuizmo::Manipulate(view, projection,
                         GetNativeOperationMode(operation_),
                         ImGuizmo::MODE::WORLD,
                         new_model_matrix);

    if (ImGuizmo::IsUsing())
        Manipulate(movable_object_, new_model_matrix, operation_);
}

void SceneManipulator::Manipulate(std::shared_ptr<MovableObject> movable_object,
                                  const float *new_model_matrix,
                                  SceneManipulatorOperation operation) {
    float translate_raw[3];
    float rotation_raw[3];
    float scale_raw[3];
    ImGuizmo::DecomposeMatrixToComponents(new_model_matrix,
                                          translate_raw,
                                          rotation_raw,
                                          scale_raw);

    if (operation == SceneManipulatorOperation::TRANSLATE) {
        auto v = glm::make_vec3(translate_raw);
        movable_object->moveTo(v);
    }
    else if (operation == SceneManipulatorOperation::ROTATE) {
        auto v = glm::make_vec3(rotation_raw);
        movable_object->rotateTo(v);
    }
    else if (operation == SceneManipulatorOperation::SCALE) {
        auto v = glm::make_vec3(scale_raw);
        movable_object->scale(v);
    }
}

ImGuizmo::OPERATION SceneManipulator::GetNativeOperationMode(
        SceneManipulatorOperation operation) {
    switch (operation) {
        case SceneManipulatorOperation::TRANSLATE:
            return ImGuizmo::OPERATION::TRANSLATE;
        case SceneManipulatorOperation::ROTATE:
            return ImGuizmo::OPERATION::ROTATE;
        case SceneManipulatorOperation::SCALE:
            return ImGuizmo::OPERATION::SCALE;
    }
}
}