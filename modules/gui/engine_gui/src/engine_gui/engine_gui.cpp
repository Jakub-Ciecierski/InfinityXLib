#include "engine_gui/engine_gui.h"

#include <engine_gui/views/main_menu.h>
#include <engine_gui/views/scene_view.h>
#include <engine_gui/views/physics_simulation_view.h>
#include <engine_gui/views/imgui_demo_view.h>

#include <gui/imgui/imgui.h>

namespace ifx{

EngineGUI::EngineGUI(EngineGUICreateParams& create_params) :
        main_menu_(create_params.main_menu),
        scene_view_(create_params.scene_view),
        physics_simulation_view_(create_params.physics_simulation_view),
        imgui_demo_view_(create_params.imgui_demo_view){}

EngineGUI::~EngineGUI(){}

void EngineGUI::Render(){
    if(main_menu_)
        main_menu_->Render();
    if(scene_view_)
        scene_view_->Render();
    if(physics_simulation_view_)
        physics_simulation_view_->Render();
    if(imgui_demo_view_)
        imgui_demo_view_->Render();
}

}
