#include "editor/window_views/screen_window_view.h"

#include <editor/views/soft_body_view.h>
#include <editor/views/scene_view.h>

#include <gui/imgui/imgui.h>

namespace ifx{

ScreenWindowView::ScreenWindowView(
        std::shared_ptr<SceneView> scene_screen_view,
        std::shared_ptr<SoftBodyView> soft_body_view) :
        WindowView(
                std::vector<std::shared_ptr<View>>{
                        scene_screen_view,
                        soft_body_view},
                "Middle Screen"),
        scene_screen_view_(scene_screen_view),
        soft_body_view_(soft_body_view){}

void ScreenWindowView::Render(){
    ImGuiStyle& style = ImGui::GetStyle();
    auto old_windowbg = style.Colors[ImGuiCol_WindowBg];
    if(selected_view_ && selected_view_ == scene_screen_view_){
        style.Colors[ImGuiCol_WindowBg].w = 0;
    }

    WindowView::Render();

    style.Colors[ImGuiCol_WindowBg] = old_windowbg;
}

}
