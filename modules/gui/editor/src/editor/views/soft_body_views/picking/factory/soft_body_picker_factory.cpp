#include "editor/views/soft_body_views/picking/factory/soft_body_picker_factory.h"

#include <editor/views/soft_body_views/picking/soft_body_picker.h>
#include <editor/views/soft_body_views/picking/ray_casting.h>
#include <editor/views/soft_body_views/picking/box_casting.h>
#include <editor/views/soft_body_views/picking/soft_body_node_selection.h>

#include <graphics/rendering/renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/model/mesh.h>
#include <graphics/shaders/data/shader_data.h>
#include "graphics/model/model_creator.h"

#include <game/architecture/engine_architecture.h>
#include <game/resources/resource_context.h>
#include <game/components/render/render_component.h>
#include <game/game_object.h>
#include <game/game_component.h>

#include <common/unique_ptr.h>

namespace ifx {

const std::string BOX_SELECTOR_RENDERING_EFFECT_NAME =
    "soft_body_editor/box_selector.prog";

std::unique_ptr<SoftBodyPicker> SoftBodyPickerFactory::Create(
    std::shared_ptr<EngineArchitecture> new_engine_architecture,
    std::shared_ptr<EngineArchitecture> old_engine_architecture){
    auto ray_casting = ifx::make_unique<RayCasting>();
    auto box_casting = CreateBoxCasting(new_engine_architecture,
                                        old_engine_architecture);

    auto node_selection = ifx::make_unique<SoftBodyNodeSelection>();

    auto soft_body_picker = ifx::make_unique<SoftBodyPicker>(
        std::move(ray_casting),
        std::move(box_casting),
        std::move(node_selection));

    return soft_body_picker;
}

std::unique_ptr<BoxCasting> SoftBodyPickerFactory::CreateBoxCasting(
    std::shared_ptr<EngineArchitecture> new_engine_architecture,
    std::shared_ptr<EngineArchitecture> old_engine_architecture){

    auto box_rendering_effect = CreateRenderingEffect(old_engine_architecture);
    new_engine_architecture->engine_systems.renderer->scene_renderer()->
        Add(box_rendering_effect);


    // Position, Normal, TexCoord
    std::vector<Vertex> vertices = {
        // Front
        Vertex{glm::vec3(1.0f, 1.0f, -1.0f),
               glm::vec3(0.0f, 0.0f, -1.0f),
               glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, -1.0f, -1.0f),
               glm::vec3(0.0f, 0.0f, -1.0f),
               glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f),
               glm::vec3(0.0f, 0.0f, -1.0f),
               glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 1.0f, -1.0f),
               glm::vec3(0.0f, 0.0f, -1.0f),
               glm::vec2(0.0f, 1.0f)}
    };

    std::vector<GLuint> indices = {
        3, 1, 0, 3, 2, 1
    };

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices));
    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh));

    auto model_creator = new_engine_architecture->engine_contexts
        .resource_context->model_creator();
    auto model = model_creator->MakeModel(ifx::NO_FILEPATH, std::move(meshes));

    auto render_component = std::make_shared<RenderComponent>(model);
    new_engine_architecture->engine_systems.renderer->scene_renderer()->Add(
        render_component);
    if(box_rendering_effect)
        box_rendering_effect->RegisterRenderObject(render_component);

    auto box_casting = ifx::make_unique<BoxCasting>(render_component);

    return box_casting;
}

std::shared_ptr<RenderingEffect> SoftBodyPickerFactory::CreateRenderingEffect(
    std::shared_ptr<EngineArchitecture> old_engine_architecture){
    auto old_rendering_effects
        = old_engine_architecture->engine_systems.renderer->
            scene_renderer()->rendering_effects();
    for (auto &rendering_effect : old_rendering_effects) {
        if (rendering_effect->name() == BOX_SELECTOR_RENDERING_EFFECT_NAME) {
            auto box_rendering_effect =
                std::make_shared<RenderingEffect>(*rendering_effect);
            return box_rendering_effect;
        }
    }
    return nullptr;
}

}