#include "editor/editor.h"

#include <editor/views/main_menu.h>
#include <editor/views/scene_view.h>
#include <editor/views/physics_simulation_view.h>
#include <editor/views/imgui_demo_view.h>
#include <editor/scene_manipulator.h>

#include <gui/theme.h>

namespace ifx{

Editor::Editor(EngineGUICreateParams& create_params) :
        main_menu_(create_params.main_menu),
        scene_view_(create_params.scene_view),
        physics_simulation_view_(create_params.physics_simulation_view),
        imgui_demo_view_(create_params.imgui_demo_view){
    SetDefaultTheme();
}

Editor::~Editor(){}

void Editor::Render(){
    if(main_menu_)
        main_menu_->Render();
    if(scene_view_)
        scene_view_->Render();
    if(physics_simulation_view_)
        physics_simulation_view_->Render();
    if(imgui_demo_view_)
        imgui_demo_view_->Render();

    scene_view_->scene_manipulator()->Manipulate();
}

void Editor::RenderSceneObjects(){
    //scene_view_->scene_manipulator()->Manipulate();
}

void Editor::SetDefaultTheme(){
    GUIThemeDracula();
}

}
