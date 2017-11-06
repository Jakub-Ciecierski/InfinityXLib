#include "editor/views/resource_views/resource_model_view.h"

#include <resources/resource_finder.h>

#include <gui/imgui/imgui.h>

namespace ifx {

ResourceModelView::ResourceModelView(): selected_(-1){}

void ResourceModelView::Render(ResourceFinder &resource_finder) {
    if (ImGui::TreeNode("Models")) {
        RenderGroup(resource_finder);
        ImGui::TreePop();
    }
}

void ResourceModelView::RenderGroup(ResourceFinder &resource_finder){
    RenderList(resource_finder);
}

void ResourceModelView::RenderList(ResourceFinder &resource_finder){
    const auto &found_resources = resource_finder.found_resources();
    static int selection_mask = (1 << 2);

    for (unsigned int i = 0; i < found_resources.size(); i++) {
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
                = ImGuiTreeNodeFlags_Bullet | ((selection_mask & (1 << i)) ?
                                               ImGuiTreeNodeFlags_Selected
                                                                           : 0);
        bool node_open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                           node_flags,
                                           found_resources[i].c_str());
        if (ImGui::IsItemClicked()) {
            node_clicked = i;
        }
        if (node_clicked != -1) {
            selection_mask = (1 << node_clicked);
            selected_ = i;
        }

        if (node_open) {
            ImGui::TreePop();
        }
    }
}

}