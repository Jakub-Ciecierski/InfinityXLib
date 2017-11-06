#include "editor/views/scene_views/game_component_views/render_object_views/render_object_material_view.h"

#include <game/components/render/render_component.h>
#include <game/resources/resource_context.h>

#include <gui/imgui/imgui.h>

#include <resources/resource_manager.h>
#include "resources/resource_finder.h"

#include <graphics/model/material.h>
#include <graphics/model/model.h>
#include <graphics/shaders/textures/texture_creator.h>

namespace ifx {

RenderObjectMaterialView::RenderObjectMaterialView(
        std::shared_ptr<ResourceContext> resource_creator) :
        resource_creator_(resource_creator),
        selected_asset_(-1),
        opened_texture_type_(TextureTypes::DIFFUSE),
        opened_texture_(nullptr){}

void RenderObjectMaterialView::Render(
        std::shared_ptr<RenderComponent> render_object){
    if (ImGui::TreeNodeEx("Materials",
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushItemWidth(70);
        RenderMeshes(render_object);
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }
}

void RenderObjectMaterialView::RenderMeshes(
        std::shared_ptr<RenderComponent> render_object){
    auto& models = render_object->models();
    int i = 0;
    for(auto& model : models){
        auto meshes = model->getMeshes();
        for(auto& mesh : meshes){
            RenderMaterial(i++, *mesh->material());
        }
    }
}

void RenderObjectMaterialView::RenderMaterial(int i, Material& material){
    std::string name = "Material [" + std::to_string(i+1) + "]";
    if (ImGui::TreeNodeEx(name.c_str(),
                          ImGuiTreeNodeFlags_DefaultOpen)) {
        RenderAlpha(material);
        RenderShininess(material);

        RenderTexture(material,
                      material.diffuse,
                      "Diffuse",
                      TextureTypes::DIFFUSE);
        RenderTexture(material, material.specular, "Specular",
                      TextureTypes::SPECULAR);
        RenderTexture(material, material.normal, "Normal",
                      TextureTypes::NORMAL);
        RenderTexture(material, material.displacement, "Displacement",
                      TextureTypes::DISPLACEMENT);

        ImGui::TreePop();
    }
}

void RenderObjectMaterialView::RenderAlpha(Material& material){
    ImGui::SliderFloat("Alpha", &material.alpha, 0, 1);
}

void RenderObjectMaterialView::RenderShininess(Material& material){
    ImGui::SliderFloat("Shininess", &material.shininess, 0, 100);
}

void RenderObjectMaterialView::RenderTexture(Material& material,
                                             std::shared_ptr<Texture2D> texture,
                                             const std::string &name,
                                             TextureTypes type){
    ImGui::PushID(name.c_str());

    ImGui::Bullet();
    ImGui::SameLine();
    auto open = ImGui::Button(name.c_str(), ImVec2(100, 20));
    if(open){
        opened_texture_type_ = type;
        opened_texture_ = texture;
    }
    RenderTexturePopup(material, open);

    std::string text = "none";
    if(texture){
        text = texture->filepath();
    }
    ImGui::Text(text.c_str());

    ImGui::PopID();
}

void RenderObjectMaterialView::RenderTexturePopup(Material& material,
                                                  bool open){
    if(open){
        ImGui::OpenPopup("Material Modal");
    }

    if (ImGui::BeginPopupModal("Material Modal", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::BeginChild(ImGui::GetID((void *) (intptr_t) 0),
                          ImVec2(1800 / 2.0f, 1200 / 2.0f), false,
                          ImGuiWindowFlags_HorizontalScrollbar);

        RenderAssetList(resource_creator_->resource_manager()
                                ->resource_finders().texture_finder_->
                        found_resources());
        ImGui::EndChild();
        ImGui::Separator();

        RenderFooter(material);

        ImGui::EndPopup();
    }
}

void RenderObjectMaterialView::RenderAssetList(
        const std::vector<std::string>& textures){
    static int selection_mask = (1 << 2);

    for (unsigned int i = 0; i < textures.size(); i++) {
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
                = ImGuiTreeNodeFlags_Bullet | ((selection_mask & (1 << i)) ?
                                               ImGuiTreeNodeFlags_Selected
                                                                           : 0);
        bool node_open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                           node_flags,
                                           textures[i].c_str());
        if (ImGui::IsItemClicked()) {
            node_clicked = i;
        }
        if (node_clicked != -1) {
            selection_mask = (1 << node_clicked);
            selected_asset_ = i;
        }

        if (node_open) {
            ImGui::TreePop();
        }
    }
}

void RenderObjectMaterialView::RenderFooter(Material& material){
    if (ImGui::Button("OK", ImVec2(120, 0))) {
        material.AddTexture(CreateTexture(), opened_texture_type_);
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("None", ImVec2(120, 0))) {
        material.AddTexture(nullptr, opened_texture_type_);
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
        ImGui::CloseCurrentPopup();
    }
}

std::shared_ptr<Texture2D> RenderObjectMaterialView::CreateTexture(){
    auto texture_names = resource_creator_->resource_manager()
            ->resource_finders().texture_finder_->
                    found_resources();
    if(selected_asset_ > -1){
        auto filepath = texture_names[selected_asset_];
        return resource_creator_->texture_creator()->MakeTexture2DFromFile(
                filepath, opened_texture_type_
        );
    }
    return nullptr;
}

}
