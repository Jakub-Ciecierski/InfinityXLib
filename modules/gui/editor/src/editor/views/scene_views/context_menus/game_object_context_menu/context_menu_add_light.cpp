#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_light.h>

#include <game/resources/resource_context.h>
#include <game/game_object.h>
#include <game/components/lights/factory/light_component_factory.h>
#include <game/components/lights/light_spotlight_component.h>
#include <game/components/lights/light_point_component.h>
#include <game/components/lights/light_directional_component.h>

#include <gui/imgui/imgui.h>

namespace ifx {

ContextMenuAddLight::ContextMenuAddLight(){}

ContextMenuAddLight::~ContextMenuAddLight(){}

void ContextMenuAddLight::Render(
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<GameObject> game_object) {
    if (ImGui::BeginMenu("Light")) {
        if (ImGui::Selectable("Directional")) {
            auto light = LightComponentFactory().CreateDirectionalLight(
                    resource_creator->texture_creator(),
                    resource_creator->program_creator());
            game_object->Add
                    (std::dynamic_pointer_cast<GameComponent>(light));
        }
        if (ImGui::Selectable("Spotlight")) {
            auto light = LightComponentFactory().CreateSpotLight(
                    resource_creator->texture_creator(),
                    resource_creator->program_creator());
            game_object->Add(
                    std::dynamic_pointer_cast<GameComponent>(light));
        }
        if (ImGui::Selectable("Point")) {
            auto light = LightComponentFactory().CreatePointLight();
            game_object->Add(std::dynamic_pointer_cast<GameComponent>
                                     (light));
        }
        ImGui::EndMenu();
    }
}

}