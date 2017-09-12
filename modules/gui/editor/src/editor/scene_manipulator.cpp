#include "editor/scene_manipulator.h"

#include <game/game_component.h>
#include <game/components/cameras/camera_component.h>

namespace ifx {

SceneManipulator::SceneManipulator() :
    transformable_object_(nullptr),
    camera_(nullptr),
    operation_(SceneManipulatorOperation::TRANSLATE),
    show_(true) {
    ImGuizmo::Enable(true);
}

SceneManipulator::~SceneManipulator() {}

void SceneManipulator::Manipulate() {
    if (!show_)
        return;
    if (!transformable_object_ || !camera_)
        return;

    ImGuizmo::BeginFrame();

    const float *view = glm::value_ptr(camera_->getViewMatrix());
    const float *projection = glm::value_ptr(camera_->getProjectionMatrix());

    auto model = transformable_object_->GetModelMatrix();
    float *new_model_matrix = glm::value_ptr(model);

    ImGuizmo::Manipulate(view, projection,
                         GetNativeOperationMode(operation_),
                         ImGuizmo::MODE::WORLD,
                         new_model_matrix);

    if (ImGuizmo::IsUsing())
        Manipulate(transformable_object_, new_model_matrix, operation_);
}

void SceneManipulator::Manipulate(std::shared_ptr<Transformable> movable_object,
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
    } else if (operation == SceneManipulatorOperation::ROTATE) {
        auto v = glm::make_vec3(rotation_raw);
        movable_object->rotateTo(v);
    } else if (operation == SceneManipulatorOperation::SCALE) {
        auto v = glm::make_vec3(scale_raw);
        movable_object->scale(v);
    }
}

ImGuizmo::OPERATION SceneManipulator::GetNativeOperationMode(
    SceneManipulatorOperation operation) {
    switch (operation) {
        case SceneManipulatorOperation::TRANSLATE:return ImGuizmo::OPERATION::TRANSLATE;
        case SceneManipulatorOperation::ROTATE:return ImGuizmo::OPERATION::ROTATE;
        case SceneManipulatorOperation::SCALE:return ImGuizmo::OPERATION::SCALE;
    }
    return ImGuizmo::OPERATION::TRANSLATE;
}
}