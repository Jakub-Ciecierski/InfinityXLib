#include "editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object.h"

#include <gui/imgui/imgui.h>

#include <game/game_object.h>
#include <game/resources/resource_context.h>

#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_parametric_equation.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_asset.h>

#include "graphics/model_loader/parametric_loader/parametric_interpreter.h"

#include <common/unique_ptr.h>

namespace ifx {

ContextMenuAddRenderObject::ContextMenuAddRenderObject(){
    context_menu_add_render_object_parametric_equation_ =
            make_unique<ContextMenuAddRenderObjectParametricEquation>();

    context_menu_add_render_object_asset_ =
            ifx::make_unique<ContextMenuAddRenderObjectAsset>();
}

void ContextMenuAddRenderObject::Render(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object){
    if (ImGui::BeginMenu("Render Object")) {
        context_menu_add_render_object_parametric_equation_->
                Render(scene_renderer, resource_creator,game_object);


        ImGui::EndMenu();
    }
}
}