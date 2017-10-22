#include "editor/views/soft_body_views/load/soft_body_load_view_factory.h"

#include <editor/views/soft_body_views/load/soft_body_load_view.h>
#include <editor/views/soft_body_views/load/traction_force_recorder.h>

#include <game/architecture/engine_architecture.h>
#include <game/components/render/render_component.h>
#include <game/resources/resource_context.h>

#include "graphics/model/model_creator.h"
#include <graphics/rendering/rendering_effect.h>
#include <graphics/model/mesh.h>
#include <graphics/model_loader/model_loader.h>
#include <graphics/rendering/renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>

#include <resources/resource.h>

#include <common/unique_ptr.h>

#include <GL/glew.h>

namespace ifx {

const std::string TRACTION_FORCE_RENDERING_EFFECT_NAME =
    "soft_body_editor/traction_force.prog";

std::unique_ptr<SoftBodyLoadView> SoftBodyLoadViewFactory::Create(
    std::shared_ptr<EngineArchitecture> new_engine_architecture,
    std::shared_ptr<EngineArchitecture> old_engine_architecture,
    std::shared_ptr<SoftBodyPicker> soft_body_picker){
    auto rendering_effect = CreateRenderingEffect(old_engine_architecture);
    new_engine_architecture->engine_systems.renderer->scene_renderer()->
        Add(rendering_effect );

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(CreateLine(
        glm::vec3(0,0,0), glm::vec3(0,0,0))));

    auto model_creator = new_engine_architecture->
        engine_contexts.resource_context->model_creator();
    auto model = model_creator->MakeModel(ifx::NO_FILEPATH, std::move(meshes));

    auto render_component = std::make_shared<RenderComponent>(model);
    new_engine_architecture->engine_systems.renderer->scene_renderer()->Add(
        render_component);
    if(rendering_effect )
        rendering_effect ->RegisterRenderObject(render_component);
    render_component->do_render(false);
    render_component->SetBeforeRender([](const Program* program){
        glLineWidth(2.0f);
    });
    render_component->SetAfterRender([](const Program* program){
        glLineWidth(1.0f);
    });

    return ifx::make_unique<SoftBodyLoadView>(render_component,
                                              soft_body_picker);
}

std::shared_ptr<RenderingEffect> SoftBodyLoadViewFactory::CreateRenderingEffect(
    std::shared_ptr<EngineArchitecture> old_engine_architecture){
    auto old_rendering_effects
        = old_engine_architecture->engine_systems.renderer->
            scene_renderer()->rendering_effects();
    for (auto &rendering_effect : old_rendering_effects) {
        if (rendering_effect->name() == TRACTION_FORCE_RENDERING_EFFECT_NAME) {
            auto box_rendering_effect =
                std::make_shared<RenderingEffect>(*rendering_effect);
            return box_rendering_effect;
        }
    }
    return nullptr;
}

std::unique_ptr<Mesh> SoftBodyLoadViewFactory::CreateLine(const glm::vec3 &p1,
                                                          const glm::vec3 &p2) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    vertices.push_back(Vertex{
        p1, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)});
    vertices.push_back(Vertex{
        p2, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)});
    indices.push_back(0);
    indices.push_back(1);

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices));
    mesh->primitive_draw_mode(PrimitiveDrawMode::LINES);

    return mesh;
}


}