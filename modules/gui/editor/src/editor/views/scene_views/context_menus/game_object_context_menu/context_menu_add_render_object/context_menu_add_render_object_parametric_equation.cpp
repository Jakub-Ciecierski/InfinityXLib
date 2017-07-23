#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_parametric_equation.h>

#include <game/game_object.h>
#include <game/resources/resource_context.h>
#include <game/components/render/render_component.h>

#include <gui/imgui/imgui.h>

#include <graphics/model_loader/parametric_loader/parametric_interpreter.h>
#include <graphics/model_loader/parametric_loader/factory/parametric_equation_expressions_factory.h>
#include <graphics/model_loader/parametric_loader/model_parametric_loader.h>
#include <graphics/shaders/loaders/program_loader.h>
#include "graphics/shaders/program_creator.h"

#include "resources/resource_manager.h"

namespace ifx {

ContextMenuAddRenderObjectParametricEquation
        ::ContextMenuAddRenderObjectParametricEquation(){
    parametric_equation_expressions_ = std::move
            (CreateDefaultParametricEquationExpression());
}

ContextMenuAddRenderObjectParametricEquation::
~ContextMenuAddRenderObjectParametricEquation(){}

void ContextMenuAddRenderObjectParametricEquation::Render(
        std::shared_ptr <ResourceContext> resource_creator,
        std::shared_ptr <GameObject> game_object) {
    if (ImGui::Button("Parametric Equation")) {
        ImGui::OpenPopup("Parametric Equation");
    }
    if (ImGui::BeginPopupModal("Parametric Equation", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        RenderWindow(resource_creator, game_object);

        ImGui::EndPopup();
    }
}

std::unique_ptr<ParametricEquationExpressions>
ContextMenuAddRenderObjectParametricEquation::CreateDefaultParametricEquationExpression(){
    return ParametricEquationExpressionsFactory().CreateSphere();
}

void ContextMenuAddRenderObjectParametricEquation::RenderWindow(
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object){
    RenderExpressions();
    ImGui::Separator();
    RenderVariables();
    ImGui::Separator();
    RenderPrecision();
    ImGui::Separator();
    RenderFooter(resource_creator, game_object);
}

void ContextMenuAddRenderObjectParametricEquation::RenderExpressions(){
    ImGui::PushItemWidth(150);

    RenderInputExpression("X", parametric_equation_expressions_->Px);
    ImGui::SameLine();
    RenderInputExpression("X Du", parametric_equation_expressions_->Px_du);
    ImGui::SameLine();
    RenderInputExpression("X Dv", parametric_equation_expressions_->Px_dv);

    RenderInputExpression("Y", parametric_equation_expressions_->Py);
    ImGui::SameLine();
    RenderInputExpression("Y Du", parametric_equation_expressions_->Py_du);
    ImGui::SameLine();
    RenderInputExpression("Y Dv", parametric_equation_expressions_->Py_dv);

    RenderInputExpression("Z", parametric_equation_expressions_->Pz);
    ImGui::SameLine();
    RenderInputExpression("Z Du", parametric_equation_expressions_->Pz_du);
    ImGui::SameLine();
    RenderInputExpression("Z Dv", parametric_equation_expressions_->Pz_dv);

    ImGui::PopItemWidth();
}

void ContextMenuAddRenderObjectParametricEquation::RenderVariables(){
    ImGui::PushItemWidth(50);

    RenderInputExpression("u start", parametric_equation_expressions_->u_start);
    ImGui::SameLine();
    RenderInputExpression("u end", parametric_equation_expressions_->u_end);

    RenderInputExpression("v start", parametric_equation_expressions_->v_start);
    ImGui::SameLine();
    RenderInputExpression("v end", parametric_equation_expressions_->v_end);

    ImGui::PopItemWidth();

}

void ContextMenuAddRenderObjectParametricEquation::RenderPrecision(){
    ImGui::PushItemWidth(50);

    ImGui::SliderInt("u precision",
                     &parametric_equation_expressions_->u_precision,
                     1, 1024);
    ImGui::SameLine();
    ImGui::SliderInt("v precision",
                     &parametric_equation_expressions_->v_precision,
                     1, 1024);

    ImGui::PopItemWidth();
}

void ContextMenuAddRenderObjectParametricEquation::RenderFooter(
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object) {
    if (ImGui::Button("OK", ImVec2(120, 0))) {
        game_object->Add(CreateRenderObject(resource_creator));

        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
        ImGui::CloseCurrentPopup();
    }
}

std::shared_ptr<RenderComponent>
ContextMenuAddRenderObjectParametricEquation::CreateRenderObject(
        std::shared_ptr<ResourceContext> resource_creator){
    auto parametric_equation = ParametricInterpreter().Interpret(
                    *parametric_equation_expressions_.get());
    auto model = ModelParametricLoader().CreateModel(
            *parametric_equation.get(),
            resource_creator->model_creator());

    auto resource_path =
            resource_creator->program_creator()->resource_manager()
                    ->resource_path();
    std::string vertex_path =
            resource_path->GetResourcePath("main/main.vs",
                                           ifx::ResourceType::SHADER);
    std::string fragment_path =
            resource_path->GetResourcePath("main/main.fs",
                                           ifx::ResourceType::SHADER);
    auto program
            = ProgramLoader(resource_creator->program_creator()).CreateProgram(
                    vertex_path, fragment_path);

    auto render_object = std::make_shared<RenderComponent>(model);
    render_object->addProgram(program);

    return render_object;
}

void ContextMenuAddRenderObjectParametricEquation::RenderInputExpression(
        std::string name, std::string& expression){
    constexpr int raw_size = 1024;
    char raw_text[raw_size];

    auto copied_size = expression.copy(raw_text, expression.size());
    raw_text[copied_size] = '\0';

    ImGui::InputText(name.c_str(), raw_text, raw_size);

    expression = std::string(raw_text);
}

}