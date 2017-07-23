#include "editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object.h"

#include <gui/imgui/imgui.h>
#include <game/game_object.h>
#include <game/resources/resource_context.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_parametric_equation.h>

namespace ifx {

ContextMenuAddRenderObject::ContextMenuAddRenderObject(){
    context_menu_add_render_object_parametric_equation_.reset(
            new(ContextMenuAddRenderObjectParametricEquation));
}

ContextMenuAddRenderObject::~ContextMenuAddRenderObject(){}

void ContextMenuAddRenderObject::Render(
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object){
    if (ImGui::BeginMenu("Render Object")) {
        context_menu_add_render_object_parametric_equation_->
                Render(resource_creator,game_object);

        ImGui::EndMenu();
    }
}
}