#include "editor/views/factory/soft_body_view_factory.h"

#include "editor/views/soft_body_view.h"

#include <game/factory/game_systems_factory.h>
#include <game/game_updater.h>
#include <game/scene_container.h>
#include <game/game_object.h>
#include <game/resources/resource_context.h>
#include <game/architecture/engine_architecture.h>
#include <game/components/cameras/factory/camera_factory.h>
#include <game/components/lights/factory/light_component_factory.h>
#include "game/components/lights/light_directional_component.h"
#include "game/components/cameras/camera_component.h"

#include <graphics/factory/fbo_renderer_factory.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>

#include <common/unique_ptr.h>

namespace ifx{

SoftBodyViewFactory::SoftBodyViewFactory(
        std::shared_ptr<EngineArchitecture> engine_architecture) :
        engine_architecture_(engine_architecture){}

std::shared_ptr<View> SoftBodyViewFactory::Create(){
    auto engine_architecture = CreateEngineArchitecture();

    SetRendererSettings(engine_architecture->engine_systems.renderer);
    SetDefaultScene(engine_architecture ->engine_systems.scene_container);

    auto game_updater = ifx::make_unique<GameUpdater>(engine_architecture);
    auto soft_body_view = std::make_shared<SoftBodyView>(
            std::move(game_updater));

    return soft_body_view;
}

std::shared_ptr<EngineArchitecture>
SoftBodyViewFactory::CreateEngineArchitecture(){
    auto game_systems_factory = CreateGameSystemsFactory();

    auto engine_architecture = std::make_shared<EngineArchitecture>();
    engine_architecture->window = engine_architecture_->window;
    engine_architecture->engine_contexts
            = engine_architecture_->engine_contexts;
    engine_architecture->engine_systems = game_systems_factory->Create(
            engine_architecture_->window,
            engine_architecture_->engine_contexts);
    engine_architecture->window = nullptr;

    return engine_architecture;
}

std::unique_ptr<GameSystemsFactory>
SoftBodyViewFactory::CreateGameSystemsFactory(){
    auto game_systems_factory = ifx::make_unique<GameSystemsFactory>();

    game_systems_factory->SetGUIFactory(nullptr);
    game_systems_factory->SetControlsFactory(nullptr);
    game_systems_factory->SetRendererFactory(
            std::make_shared<FBORendererFactory>());

    return game_systems_factory;
}

void SoftBodyViewFactory::SetDefaultScene(
        std::shared_ptr<SceneContainer> scene){
    auto game_object = scene->CreateAndAddEmptyGameObject();
    auto camera = CameraFactory().CreateCamera(
            engine_architecture_->window.get());
    game_object->Add(std::dynamic_pointer_cast<GameComponent>(camera));

    // Lights
    auto light_game_object = scene->CreateAndAddEmptyGameObject();
    game_object->Add(
            LightComponentFactory().CreateDirectionalLight(
                    engine_architecture_->engine_contexts.resource_context->
                            texture_creator(),
                    engine_architecture_->engine_contexts.resource_context->
                            program_creator()));

    // Test Box
}

void SoftBodyViewFactory::SetRendererSettings(
        std::shared_ptr<Renderer> renderer){
    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(renderer);
    fbo_renderer->EnableRenderToScreen(false);

    auto& rendering_effects = renderer->scene_renderer()->rendering_effects();
    for(auto& rendering_effect : rendering_effects){
        if(rendering_effect->name() == "main.prog"){
            auto main_rendering_state = std::make_shared<RenderingEffect>(
                    rendering_effect->program(),
                    rendering_effect->rendering_state(),
                    "main.prog");
            renderer->scene_renderer()->Add(main_rendering_state);
        }
    }
}

}
