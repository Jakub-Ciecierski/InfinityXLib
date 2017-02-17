#include <gui/imgui/imgui.h>
#include "engine_gui/views/scene_view/scene_manipulator_view.h"

namespace ifx{

SceneManipulatorView::SceneManipulatorView(
        std::shared_ptr<SceneManipulator> scene_manipulator) :
        scene_manipulator_(scene_manipulator),
        current_operation_(SceneManipulatorOperation::ROTATE),
        render_(true){}
SceneManipulatorView::~SceneManipulatorView(){}

void SceneManipulatorView::Render(){
    RenderConfig();
    scene_manipulator_->show(render_);
    scene_manipulator_->operation(current_operation_);
}

void SceneManipulatorView::RenderConfig(){
    ImGui::Checkbox("Show", &render_);

    static int e = 0;
    const int TRANSLATE_ID = 0;
    const int ROTATE_ID = 1;
    const int SCALE_ID = 2;
    ImGui::RadioButton("Translate", &e, TRANSLATE_ID); ImGui::SameLine();
    ImGui::RadioButton("Rotate", &e, ROTATE_ID); ImGui::SameLine();
    ImGui::RadioButton("Scale", &e, SCALE_ID);

    switch(e){
        case TRANSLATE_ID:
            current_operation_ = SceneManipulatorOperation::TRANSLATE;
            break;
        case ROTATE_ID:
            current_operation_ = SceneManipulatorOperation::ROTATE;
            break;
        case SCALE_ID:
            current_operation_ = SceneManipulatorOperation::SCALE;
            break;
    }
}

}