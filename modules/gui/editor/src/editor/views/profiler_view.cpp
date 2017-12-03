#include "editor/views/profiler_view.h"

#include <game/game_loop.h>
#include <game/game_updater.h>
#include <game/scene_container.h>

#include <graphics/rendering/renderer.h>
#include <graphics/rendering/window/window.h>

#include <physics/physics_simulation.h>

#include <gui/imgui/imgui.h>
#include <gui/gui.h>

#include <controls/controls.h>

namespace ifx {

ProfilerView::ProfilerView(std::shared_ptr<GameLoop> game_loop) :
        View("Profiler"),
        game_loop_(game_loop){}

void ProfilerView::Render(){
    ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 0),
                      ImVec2(-1, -1), false,
                      ImGuiWindowFlags_HorizontalScrollbar |
                              ImGuiWindowFlags_ShowBorders);

    const auto& game_updaters = game_loop_->game_updaters();
    int id = 0;
    for(const auto& game_updater : game_updaters){
        std::string name = "System[" + std::to_string(id) + "]";
        ImGui::PushID(id);
        if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            RenderProfiler(*game_updater);
            ImGui::TreePop();
        }
        ImGui::PopID();
        id++;

    }

    ImGui::EndChild();
}

void ProfilerView::RenderProfiler(const GameUpdater& game_updater){
    const auto& engine_architecture = game_updater.engine_architecture();
    double total_time = 0;

    if(engine_architecture->engine_systems.physics_simulation){
        const auto& timer = engine_architecture->engine_systems
                .physics_simulation->timer();
        total_time += timer.ElapsedMS();
    }
    if(engine_architecture->engine_systems.scene_container){
        const auto& timer = engine_architecture->engine_systems
                .scene_container->timer();
        total_time += timer.ElapsedMS();
    }
    if(engine_architecture->engine_systems.controls){
        const auto& timer = engine_architecture->engine_systems
                .controls->timer();
        total_time += timer.ElapsedMS();
    }
    if(engine_architecture->engine_systems.renderer){
        const auto& timer = engine_architecture->engine_systems
                .renderer->timer();
        total_time += timer.ElapsedMS();
    }
    if(engine_architecture->engine_systems.gui){
        const auto& timer = engine_architecture->engine_systems
                .gui->timer();
        total_time += timer.ElapsedMS();
    }
    if(engine_architecture->window){
        const auto& timer = engine_architecture->window->timer();
        total_time += timer.ElapsedMS();
    }

    ImGui::Text("%.2f [ms]: Total Time", total_time);

    if(engine_architecture->engine_systems.physics_simulation){
        const auto& timer = engine_architecture->engine_systems
                .physics_simulation->timer();
        RenderSingleProfiler("Physics", timer, total_time);
    }
    if(engine_architecture->engine_systems.scene_container){
        const auto& timer = engine_architecture->engine_systems
                .scene_container->timer();
        RenderSingleProfiler("Scene", timer, total_time);
    }
    if(engine_architecture->engine_systems.controls){
        const auto& timer = engine_architecture->engine_systems
                .controls->timer();
        RenderSingleProfiler("Controls", timer, total_time);
    }
    if(engine_architecture->engine_systems.renderer){
        const auto& timer = engine_architecture->engine_systems
                .renderer->timer();
        RenderSingleProfiler("Renderer", timer, total_time);
    }
    if(engine_architecture->engine_systems.gui){
        const auto& timer = engine_architecture->engine_systems
                .gui->timer();
        RenderSingleProfiler("GUI", timer, total_time);
    }
    if(engine_architecture->window){
        const auto& timer = engine_architecture->window->timer();
        RenderSingleProfiler("Window", timer, total_time);
    }
}

void ProfilerView::RenderSingleProfiler(const std::string &name,
                                        const UpdateTimer &timer,
                                        double total_time) {
    std::string text = "%.2f " + name;
    ImVec2 progress_bar_size{100, 20};
    ImGui::ProgressBar(timer.ElapsedMS() / total_time, progress_bar_size);
    ImGui::SameLine();
    ImGui::Text(text.c_str(), timer.ElapsedMS());
}

}