#include "engine_gui/engine_gui.h"

#include <engine_gui/views/main_menu.h>
#include <engine_gui/views/scene_view.h>
#include <gui/imgui/imgui.h>

namespace ifx{

EngineGUI::EngineGUI(EngineGUICreateParams& create_params) :
        main_menu_(create_params.main_menu),
        scene_view_(create_params.scene_view){}

EngineGUI::~EngineGUI(){}

void EngineGUI::Render(){
    ImGui::ShowTestWindow();
    if(main_menu_)
        main_menu_->Render();
    if(scene_view_)
        scene_view_->Render();
}

}
