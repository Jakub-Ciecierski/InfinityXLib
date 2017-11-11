#include <editor/views/soft_body_views/soft_body_structers.h>

#include <graphics/rendering/rendering_effect.h>

#include <game/components/render/render_component.h>
#include <game/game_object.h>

#include <RTFEM/FEM/BoundaryCondition.h>

#include <GL/glew.h>

namespace ifx {

const unsigned int MAX_RENDER_COMPONENTS = 1;

void SoftBodyRenderingEffects::Register(
        std::shared_ptr<RenderComponent> render_component){
    if(main)
        main->RegisterRenderObject(render_component);
    if(nodes)
        nodes->RegisterRenderObject(render_component);
    if(edges)
        edges->RegisterRenderObject(render_component);
    if(faces)
        faces->RegisterRenderObject(render_component);
}

SoftBodyEditorObjects::SoftBodyEditorObjects() :
        current_game_object(nullptr),
        soft_body_fem_component_builder(nullptr),
        current_fem_render_component(nullptr){}

SoftBodyEditorObjects::SoftBodyEditorObjects(
        std::shared_ptr<GameObject> current_game_object_,
        std::unique_ptr<SoftBodyFEMComponentBuilder<double>>
        soft_body_fem_component_builder_) :
        current_game_object(current_game_object_),
        soft_body_fem_component_builder(
                std::move(soft_body_fem_component_builder_)),
        current_fem_render_component(nullptr) {}

void SoftBodyEditorObjects::UpdateFEMRenderComponent(
        std::shared_ptr<RenderComponent> render_component){
    if(current_game_object && soft_body_fem_component_builder){
        current_game_object->Remove(current_fem_render_component);
        current_fem_render_component = render_component;
        current_game_object->Add(render_component);

        render_component->SetBeforeRender([](const Program* program){
            glEnable(GL_BLEND);
            glBlendEquation(GL_MAX);
        });
        render_component->SetAfterRender([](const Program* program){
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        });
    }
}

}