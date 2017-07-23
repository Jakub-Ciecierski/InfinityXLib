#include "editor/views/imgui_demo_view.h"

#include <gui/imgui/imgui.h>

namespace ifx {

ImGuiDemoView::ImGuiDemoView() : View("ImGui Demo"){
    show_ = false;
}

ImGuiDemoView::~ImGuiDemoView() {}

void ImGuiDemoView::Render() {
    if(show_)
        ImGui::ShowTestWindow();
}

void ImGuiDemoView::RenderContent() {

}

};