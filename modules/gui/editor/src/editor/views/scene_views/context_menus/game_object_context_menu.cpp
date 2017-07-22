#include "editor/views/scene_views/context_menus/game_object_context_menu.h"

#include <game/game_object.h>
#include <game/scene_container.h>
#include <game/components/lights/factory/light_component_factory.h>
#include <game/resources/resource_context.h>
#include <game/components/lights/light_spotlight_component.h>
#include <game/components/lights/light_point_component.h>
#include <game/components/lights/light_directional_component.h>

#include <gui/imgui/imgui.h>

namespace ifx {

GameObjectContextMenu::GameObjectContextMenu(
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<SceneContainer> scene) :
        resource_creator_(resource_creator),
        scene_(scene) {}

GameObjectContextMenu::~GameObjectContextMenu(){}

void GameObjectContextMenu::Render(std::shared_ptr<GameObject> game_object,
                                   int game_object_id) {
    ImGui::PushID(std::to_string(game_object_id).c_str());
    if (ImGui::BeginPopupContextItem("GameObject context menu")) {

        Add(resource_creator_, game_object, game_object_id);
        ImGui::Separator();
        Remove(scene_, game_object, game_object_id);

        ImGui::EndPopup();
    }
    ImGui::PopID();
}

void GameObjectContextMenu::Remove(std::shared_ptr<SceneContainer> scene,
                                   std::shared_ptr<GameObject> game_object,
                                   int game_object_id) {
    if (ImGui::Selectable("Remove")) {
        scene->Remove(game_object);
    }
}

void GameObjectContextMenu::Add(std::shared_ptr<ResourceContext> resource_creator,
                                std::shared_ptr<GameObject> game_object,
                                int game_object_id) {
    if (ImGui::BeginMenu("Add")) {
        AddLight(resource_creator, game_object, game_object_id);
        AddRenderObject(game_object, game_object_id);
        ImGui::EndMenu();
    }
}

void GameObjectContextMenu::AddLight(std::shared_ptr<ResourceContext> resource_creator,
                                     std::shared_ptr<GameObject> game_object,
                                     int game_object_id) {
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

void GameObjectContextMenu::AddRenderObject(std::shared_ptr<GameObject> game_object,
                                            int game_object_id) {
    if (ImGui::BeginMenu("Render Object")) {
        if (ImGui::Button("Parametric Equation")) {
            ImGui::OpenPopup("Parametric Equation");
        }
        if (ImGui::BeginPopupModal("Parametric Equation", NULL,
                                   ImGuiWindowFlags_AlwaysAutoResize)) {
            static char x_text[1024];
            ImGui::InputText("X", x_text, 1024);

            ImGui::SameLine();

            static char xdu_text[1024];
            ImGui::InputText("X Du", xdu_text, 1024);

            ImGui::SameLine();

            static char xdv_text[1024];
            ImGui::InputText("X Dv", xdv_text, 1024);

            static char y_text[1024];
            ImGui::InputText("Y", y_text, 1024);

            static char z_text[1024];
            ImGui::InputText("Z", z_text, 1024);

            ImGui::Separator();

            if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
        }
        ImGui::EndMenu();
    }
}

}

