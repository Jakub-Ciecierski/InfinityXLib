#include "editor/window_views/imgui_demo_window_view.h"

#include <gui/imgui/imgui.h>

namespace ifx {

ImGuiDemoWindowView::ImGuiDemoWindowView() : WindowView("ImGui Demo") {
    show_ = false;
}

ImGuiDemoWindowView::~ImGuiDemoWindowView() {}

void ImGuiDemoWindowView::Render() {
    if (show_)
        ImGui::ShowTestWindow();
}

void ImGuiDemoWindowView::RenderContent() {

}

};