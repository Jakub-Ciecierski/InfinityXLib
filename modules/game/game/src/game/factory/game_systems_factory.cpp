#include "game/factory/game_systems_factory.h"

#include <graphics/factory/fbo_renderer_factory.h>
#include <graphics/rendering/renderer.h>
#include <graphics/rendering/window/window.h>

#include <physics/factory/physx_physics_simulation_factory.h>

#include <controls/factory/controls_factory.h>

#include <gui/factory/gui_factory.h>

#include <game/factory/scene_container_factory.h>
#include <game/resources/resource_context.h>

namespace ifx {

GameSystemsFactory::GameSystemsFactory() {
    CreateDefaultFactories();
}

EngineSystems GameSystemsFactory::Create(
    std::shared_ptr<Window> window,
    const EngineContexts &engine_contexts) {
    EngineSystems engine_systems;

    if (renderer_factory_) {
        engine_systems.renderer = renderer_factory_->Create(
            window,
            engine_contexts.rendering_context,
            engine_contexts.resource_context->texture_creator(),
            engine_contexts.resource_context->program_creator(),
            engine_contexts.resource_context->resource_manager());
    }
    if (physics_simulation_factory_) {
        engine_systems.physics_simulation = physics_simulation_factory_->Create(
            engine_contexts.physics_context);
    }
    if (controls_factory_) {
        engine_systems.controls = controls_factory_->Create(
            engine_contexts.control_context);
    }
    if (scene_factory_) {
        engine_systems.scene_container = scene_factory_->Create(
            engine_systems.renderer->scene_renderer(),
            engine_systems.physics_simulation);
    }
    if (gui_factory_) {
        engine_systems.gui = gui_factory_->Create(engine_contexts.gui_context);
    }

    return engine_systems;
}

void GameSystemsFactory::CreateDefaultFactories() {
    scene_factory_ = std::make_shared<SceneContainerFactory>();

    renderer_factory_ = std::make_shared<FBORendererFactory>();

    physics_simulation_factory_ =
        std::make_shared<PhysxPhysicsSimulationFactory>();

    controls_factory_ = std::make_shared<ControlsFactory>();

    gui_factory_ = std::make_shared<GUIFactory>();
}

GameSystemsFactory &GameSystemsFactory::SetSceneContainerFactory(
    std::shared_ptr<SceneContainerFactory> scene_factory) {
    scene_factory_ = scene_factory;
    return *this;
}

GameSystemsFactory &GameSystemsFactory::SetRendererFactory(
    std::shared_ptr<RendererFactory> renderer_factory) {
    renderer_factory_ = renderer_factory;
    return *this;
}

GameSystemsFactory &GameSystemsFactory::SetPhysicsSimulationFactory(
    std::shared_ptr<PhysicsSimulationFactory> physics_simulation_factory) {
    physics_simulation_factory_ = physics_simulation_factory;
    return *this;
}

GameSystemsFactory &GameSystemsFactory::SetControlsFactory(
    std::shared_ptr<ControlsFactory> factory) {
    controls_factory_ = factory;
    return *this;
}

GameSystemsFactory &GameSystemsFactory::SetGUIFactory(
    std::shared_ptr<GUIFactory> factory) {
    gui_factory_ = factory;
    return *this;
}

}
