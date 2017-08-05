#include "editor/views/rendering_view/rendering_effect_view.h"

#include <editor/processes/rendering_effect_processor.h>

#include "graphics/shaders/program.h"
#include <graphics/rendering/rendering_effect.h>

#include <gui/imgui/imgui.h>
#include <gui/imgui/imgui_internal.h>

#include <boost/filesystem.hpp>

namespace ifx{

RenderingEffectView::RenderingEffectView(
        std::shared_ptr<RenderingEffectProcessor> rendering_effect_processor) :
        rendering_effect_processor_(rendering_effect_processor),
        selected_rendering_effect_(nullptr),
        render_error_window_(false) {}

void RenderingEffectView::Render(const std::vector<std::shared_ptr<RenderingEffect>>& rendering_effects ){
    RenderReloadProject();

    RenderList(rendering_effects);
    ImGui::Separator();

    if(selected_rendering_effect_){
        if(ImGui::TreeNode("Shaders")){
            RenderShaders(selected_rendering_effect_);
            ImGui::TreePop();
        }
        if(ImGui::TreeNode("Rendering State")){
            RenderState(selected_rendering_effect_);
            ImGui::TreePop();
        }

    }
}

void RenderingEffectView::RenderReloadProject(){
    if (ImGui::BeginPopupContextItem("Reload Project Context Menu")) {
        if(ImGui::Selectable("Reload Project")){
            rendering_effect_processor_->CompileAllPrograms();
        }
        ImGui::EndPopup();
    }
}

void RenderingEffectView::RenderList(const std::vector<std::shared_ptr<RenderingEffect>>& rendering_effects){
    static int selection_mask = (1 << 2);

    for(unsigned int i = 0;i < rendering_effects.size(); i++){
        int node_clicked = -1;
        ImGuiTreeNodeFlags node_flags
                = ImGuiTreeNodeFlags_Bullet | ((selection_mask & (1 << i)) ?
                                               ImGuiTreeNodeFlags_Selected : 0);
        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i,
                                           node_flags,
                                           GetBaseName(rendering_effects[i]->name()).c_str());
        if (ImGui::IsItemClicked()){
            node_clicked = i;
        }
        if (node_clicked != -1){
            selection_mask = (1 << node_clicked);
            selected_rendering_effect_ = rendering_effects[i];
        }

        if (node_open){
            ImGui::TreePop();
        }
    }
}

void RenderingEffectView::RenderShaders(std::shared_ptr<RenderingEffect> rendering_effect){
    RenderShaderReload(rendering_effect);

    auto program = rendering_effect->program();
    RenderShader(program->vertex_shader(), program, "Vertex Shader");
    RenderShader(program->fragment_shader(), program, "Fragment Shader");
    RenderShader(program->geometry_shader(), program,"Geometry Shader");
    RenderShader(program->tess_control_shader(), program,"Tessellation Control Shader");
    RenderShader(program->tess_eval_shader(), program,"Tessellation Evaluation Shader");
}

void RenderingEffectView::RenderShaderReload(
        std::shared_ptr<RenderingEffect> rendering_effect){
    if (ImGui::BeginPopupContextItem("Recompile Shaders Context Menu")) {
        if(ImGui::Selectable("Recompile Shaders")){
            rendering_effect->program()->Reload();
        }
        ImGui::EndPopup();
    }
}

void RenderingEffectView::RenderShader(Shader* shader,
                                       std::shared_ptr<Program> program,
                                       std::string shader_type_name){
    if(!shader)
        return;
    ImGui::PushID(shader_type_name.c_str());

    ImGui::Selectable(shader_type_name.c_str());
    bool shader_opened = false;
    if (ImGui::BeginPopupContextItem("Shader Context Menu")) {
        shader_opened = ImGui::Selectable("Open");
        ImGui::EndPopup();
    }
    RenderShaderWindow(shader, program, shader_opened);
    ImGui::Bullet();
    ImGui::SameLine();
    if(shader){
        ImGui::TextWrapped(GetBaseShaderName(shader->file_path()).c_str());
    }else{
        ImGui::Text("Empty");
    }
    ImGui::Separator();

    ImGui::PopID();
}

void RenderingEffectView::RenderShaderWindow(Shader* shader,
                                             std::shared_ptr<Program> program,
                                             bool open) {
    if (!shader)
        return;
    constexpr int raw_size = 10240 * 16;
    static char raw_text[raw_size];
    ShaderError shader_error{false, ""};

    if (open) {
        auto source = shader->shader_source();
        auto copied_size = source.copy(raw_text, source.size());
        raw_text[copied_size] = '\0';

        ImGui::OpenPopup("Shader");
    }
    if (ImGui::BeginPopupModal("Shader", NULL)) {
        ImGui::InputTextMultiline("Shader", raw_text, IM_ARRAYSIZE(raw_text),
                                  ImVec2(800, 600),
                                  ImGuiInputTextFlags_AllowTabInput);
        ImGui::Separator();
        if (ImGui::Button("Save & Compile", ImVec2(120, 0))) {
            boost::filesystem::save_string_file(
                    boost::filesystem::path(shader->file_path()),
                    std::string(raw_text));
            shader_error = shader->Reload();
            if (shader_error.error_occured) {
                render_error_window_ = true;
                shader_error_message_ = shader_error.message;
            } else{
                program->Reload();
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Close", ImVec2(120, 0)))
            ImGui::CloseCurrentPopup();

        if(render_error_window_)
            RenderErrorWindow(shader_error);

        ImGui::EndPopup();
    }
}

void RenderingEffectView::RenderErrorWindow(const ShaderError& shader_error){
    ImGui::OpenPopup("Shader Error");
    if (ImGui::BeginPopupModal("Shader Error", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(shader_error_message_.c_str());
        ImGui::Separator();
        if(ImGui::Button("OK", ImVec2(100, 0))) {
            render_error_window_ = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void RenderingEffectView::RenderState(std::shared_ptr<RenderingEffect> rendering_effect){

}

std::string RenderingEffectView::GetBaseName(const std::string& name){
    std::string base_name = "";
    for(unsigned int i = 0; i < name.length(); i++){
        if(name[i] == '.')
            break;
        base_name += name[i];
    }
    return base_name;
}

std::string RenderingEffectView::GetBaseShaderName(const std::string& name){
    auto pos = name.find_last_of("/");
    return name.substr(pos+1, name.length());
}

}