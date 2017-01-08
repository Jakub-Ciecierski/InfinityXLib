#include <gui/imgui/imgui.h>
#include "engine_gui/views/scene_manipulator_view.h"

namespace ifx{

SceneManipulatorView::SceneManipulatorView() :
        current_operation_(SceneManipulatorOperation::ROTATE),
        render_(true){}
SceneManipulatorView::~SceneManipulatorView(){}

void SceneManipulatorView::Render(std::shared_ptr<MovableObject> movable_object,
                                  std::shared_ptr<Camera> camera){
    RenderConfig();
    if(render_)
        scene_manipulator_->Manipulate(movable_object,
                                       camera, current_operation_);
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