#include "editor/views/soft_body_views/soft_body_selector.h"

#include <editor/views/soft_body_views/soft_body_structers.h>

#include <graphics/rendering/rendering_effect.h>

#include <game/components/render/render_component.h>
#include <game/game_object.h>
#include <game/game_component.h>
#include <game/scene_container.h>
#include "game/components/physics/soft_body_fem_component.h"

#include <common/unique_ptr.h>

#include "RTFEM/FEM/FEMModel.h"
#include <RTFEM/FEM/FEMGeometry.h>

namespace ifx {

SoftBodySelector::SoftBodySelector(std::shared_ptr<SceneContainer> scene) :
    scene_(scene) {}

void SoftBodySelector::Select(
    std::shared_ptr<GameObject> selected_game_object,
    SoftBodyRenderingEffects &rendering_effects,
    SoftBodyObjects &soft_body_objects) {
    RemoveCurrentGameObject(soft_body_objects);

    if (!CheckSelectedGameObjectCorrectness(selected_game_object,
                                            soft_body_objects)) {
        return;
    }

    soft_body_objects = CreateNewGameObject(selected_game_object,
                                            rendering_effects);
}

void SoftBodySelector::RemoveCurrentGameObject(
    SoftBodyObjects &soft_body_objects) {
    if (soft_body_objects.current_game_object) {
        scene_->Remove(soft_body_objects.current_game_object);
    }
    soft_body_objects = SoftBodyObjects{nullptr, nullptr, nullptr, nullptr};
}

bool SoftBodySelector::CheckSelectedGameObjectCorrectness(
    std::shared_ptr<GameObject> selected_game_object,
    SoftBodyObjects &soft_body_objects) {
    if (!selected_game_object) {
        soft_body_objects = SoftBodyObjects{nullptr, nullptr, nullptr, nullptr};
        return false;
    }

    auto render_components = selected_game_object->GetComponents(
        std::move(GameComponentType::RENDER));
    if (render_components.size() != MAX_RENDER_COMPONENTS) {
        soft_body_objects = SoftBodyObjects{nullptr, nullptr, nullptr, nullptr};
        return false;
    }

    return true;
}

SoftBodyObjects SoftBodySelector::CreateNewGameObject(
    std::shared_ptr<GameObject> selected_game_object,
    SoftBodyRenderingEffects &rendering_effects) {
    SoftBodyObjects soft_body_objects;

    auto render_components = selected_game_object->GetComponents(
        std::move(GameComponentType::RENDER));

    soft_body_objects.current_game_object
        = scene_->CreateAndAddEmptyGameObject();

    soft_body_objects.soft_body_fem =
        std::make_shared<SoftBodyFEMComponent<double>>(
            std::move(ifx::make_unique<rtfem::FEMModel<double>>()));

    for (auto &render_component : render_components) {
        soft_body_objects.triangle_mesh = std::make_shared<RenderComponent>(
            std::dynamic_pointer_cast<RenderComponent>(
                render_component)->models());
        RegisterGameObjectToRenderingEffects(soft_body_objects.triangle_mesh,
                                             rendering_effects);

        soft_body_objects.current_game_object->Add(
            soft_body_objects.triangle_mesh);
    }
    return soft_body_objects;
}

void SoftBodySelector::RegisterGameObjectToRenderingEffects(
    std::shared_ptr<RenderComponent> render_component,
    SoftBodyRenderingEffects &rendering_effects) {
    rendering_effects.main->RegisterRenderObject(render_component);
    rendering_effects.edges->RegisterRenderObject(render_component);
    rendering_effects.nodes->RegisterRenderObject(render_component);
    rendering_effects.faces->RegisterRenderObject(render_component);
}

}