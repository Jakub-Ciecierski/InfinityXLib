#include "editor/window_views/main_menu_items/main_menu_update_item.h"

#include <game/architecture/engine_architecture.h>
#include <game/scene_container.h>

#include <controls/controls.h>

#include <common/updatable.h>

#include <physics/physics_simulation.h>

#include <gui/imgui/imgui.h>
#include <gui/gui.h>

#include <graphics/rendering/renderer.h>

namespace ifx {

void MainMenuUpdateItem::Render(EngineArchitecture& engine_architecture){
    if (ImGui::Button("Engine Update Frequency"))
        ImGui::OpenPopup("Engine Update Frequency");
    if (ImGui::BeginPopupModal("Engine Update Frequency", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {

        RenderEngineUpdateSettings(engine_architecture);
        RenderFooter();

        ImGui::EndPopup();
    }
}

void MainMenuUpdateItem::RenderEngineUpdateSettings(
    EngineArchitecture &engine_architecture) {
    ImGui::Text("Time Step [Hz]");
    RenderUpdateSettings(engine_architecture.engine_systems.physics_simulation,
                         "Physics");
    RenderUpdateSettings(engine_architecture.engine_systems.renderer,
                         "Renderer");
    RenderUpdateSettings(engine_architecture.engine_systems.scene_container,
                         "Scene Container");
    RenderUpdateSettings(engine_architecture.engine_systems.gui, "GUI");
    RenderUpdateSettings(engine_architecture.engine_systems.controls,
                         "Input Controls");
}

void MainMenuUpdateItem::RenderUpdateSettings(
    std::shared_ptr<Updatable> updatable,
    std::string name) {
    float time_step_hz = 1.0f / updatable->fixed_time_delta();

    ImGui::PushItemWidth(75);

    if (ImGui::InputFloat(name.c_str(), &time_step_hz)) {
        float time_step_s = 1.0f / time_step_hz;
        updatable->fixed_time_delta(time_step_s);
    }

    ImGui::PopItemWidth();
}

void MainMenuUpdateItem::RenderFooter(){
    if (ImGui::Button("OK", ImVec2(120, 0))) {
        ImGui::CloseCurrentPopup();
    }
}

}