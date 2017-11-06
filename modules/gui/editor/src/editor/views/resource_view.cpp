#include "editor/views/resource_view.h"

#include <resources/resource_finder.h>
#include <resources/resource_manager.h>

#include <game/resources/resource_context.h>

#include <gui/imgui/imgui.h>

#include <common/unique_ptr.h>

#include "editor/views/resource_views/resource_model_view.h"
#include "editor/views/resource_views/resource_texture_view.h"

namespace ifx {

ResourceView::ResourceView(
        std::shared_ptr<ResourceContext> resource_context) :
        View("Resources"),
        resource_context_(resource_context) {
    model_view_ = ifx::make_unique<ResourceModelView>();
    texture_view_ = ifx::make_unique<ResourceTextureView>();
}

void ResourceView::Render(){
    ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 0),
                      ImVec2(-1, -1), false,
                      ImGuiWindowFlags_HorizontalScrollbar);
    RenderUpdate();
    RenderTextures();
    RenderModels();

    ImGui::EndChild();
}


void ResourceView::RenderUpdate(){
    if(ImGui::Button("Reload")){
        auto& resource_finders =
                resource_context_->resource_manager()->resource_finders();
        resource_finders.model_finder_->Update();
        resource_finders.texture_finder_->Update();
    }
}

void ResourceView::RenderTextures(){
    auto& resource_finders =
            resource_context_->resource_manager()->resource_finders();
    texture_view_->Render(*resource_finders.texture_finder_);
}

void ResourceView::RenderModels(){
    auto& resource_finders =
            resource_context_->resource_manager()->resource_finders();
    model_view_->Render(*resource_finders.model_finder_);
}

}