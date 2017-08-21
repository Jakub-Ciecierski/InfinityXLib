#include "game/factory/game_factory.h"

#include <game/factory/game_loop_factory.h>
#include <game/game_loop.h>
#include <game/factory/scene_container_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <game/resources/factory/resource_context_factory.h>
#include <game/resources/resource_context.h>

#include <graphics/rendering/renderer.h>
#include <graphics/rendering/context/rendering_context.h>
#include <graphics/factory/renderer_factory.h>
#include <graphics/rendering/window/factory/window_factory.h>
#include "graphics/rendering/context/factory/rendering_context_opengl_factory.h"

#include <physics/factory/physics_simulation_factory.h>
#include <physics/factory/bullet_physics_simulation_factory.h>

#include <controls/factory/controls_factory.h>
#include <controls/context/factory/control_context_glfw_factory.h>

#include <gui/context/factory/gui_context_factory.h>
#include <gui/context/factory/glfw/gui_glfw_context_factory.h>
#include <gui/factory/gui_factory.h>
#include <gui/gui.h>
#include <graphics/factory/fbo_renderer_factory.h>

namespace ifx {

GameFactory::GameFactory(){
    CreateDefaultFactories();
}

GameFactory::~GameFactory(){}

void GameFactory::CreateDefaultFactories(){
    window_factory_ = std::make_shared<WindowFactory>();

    rendering_context_factory_ 
            = std::make_shared<RenderingContextOpenglFactory>();

    resource_context_factory_ = std::make_shared<ResourceContextFactory>();

    game_loop_factory_
            = std::make_shared<GameLoopFactory>();

    scene_factory_ = std::make_shared<SceneContainerFactory>();

    renderer_factory_ = std::make_shared<FBORendererFactory>();
    //renderer_factory_ = std::make_shared<RendererFactory>();

    physics_simulation_factory_ =
            std::make_shared<BulletPhysicsSimulationFactory>();

    controls_factory_ = std::make_shared<ControlsFactory>();

    control_context_factory_ = std::make_shared<ControlContextGLFWFactory>();

    gui_context_factory_ = std::make_shared<GUIGLFWContextFactory>();

    gui_factory_ = std::make_shared<GUIFactory>();
}

GameFactory& GameFactory::SetWindowFactory(
        std::shared_ptr<WindowFactory> factory){
    window_factory_ = factory;
    return *this;
}

GameFactory& GameFactory::SetRenderingContextFactory(
        std::shared_ptr<RenderingContextFactory> factory){
    rendering_context_factory_ = factory;
    return *this;
}

GameFactory& GameFactory::SetResourceContextFactory(
        std::shared_ptr<ResourceContextFactory> factory){
    resource_context_factory_ = factory;
    return *this;
}

GameFactory& GameFactory::SetGameLoopFactory(
        std::shared_ptr<GameLoopFactory> game_loop_factory){
    game_loop_factory_ = game_loop_factory;
    return *this;
}

GameFactory& GameFactory::SetSceneContainerFactory(
        std::shared_ptr<SceneContainerFactory> scene_factory){
    scene_factory_ = scene_factory;
    return *this;
}

GameFactory& GameFactory::SetRendererFactory(
        std::shared_ptr<RendererFactory> renderer_factory){
    renderer_factory_ = renderer_factory;
    return *this;
}

GameFactory& GameFactory::SetPhysicsSimulationFactory(
        std::shared_ptr<PhysicsSimulationFactory> physics_simulation_factory){
    physics_simulation_factory_ = physics_simulation_factory;
    return *this;
}

GameFactory& GameFactory::SetControlsFactory(
        std::shared_ptr<ControlsFactory> factory){
    controls_factory_ = factory;
    return *this;
}

GameFactory& GameFactory::SetControlContextFactory(
        std::shared_ptr<ControlContextFactory> factory){
    control_context_factory_ = factory;
    return *this;
}

GameFactory &
GameFactory::SetGUIContextFactory(std::shared_ptr<GUIContextFactory> factory) {
    gui_context_factory_ = factory;
    return *this;
}

GameFactory &GameFactory::SetGUIFactory(std::shared_ptr<GUIFactory> factory) {
    gui_factory_ = factory;
    return *this;
}

std::shared_ptr<Game> GameFactory::Create(){
    auto engine_architecture = std::make_shared<EngineArchitecture>();

    engine_architecture->engine_contexts = CreateEngineContexts();
    engine_architecture->window
            = CreateWindow(engine_architecture->engine_contexts);
    engine_architecture->engine_systems = CreateEngineSystems(
            engine_architecture->window, engine_architecture->engine_contexts);

    auto game_loop = CreateGameLoop(engine_architecture);

    auto game = std::make_shared<Game>(game_loop,
                                       engine_architecture);

    return game;
}

EngineContexts GameFactory::CreateEngineContexts(){
    EngineContexts engine_contexts;

    if(rendering_context_factory_) {
        engine_contexts.rendering_context
                = rendering_context_factory_->Create();
    }
    if(resource_context_factory_) {
        engine_contexts.resource_context =
                resource_context_factory_->Create();
    }
    if(control_context_factory_) {
        engine_contexts.control_context
                = control_context_factory_->Create();
    }
    if(gui_context_factory_) {
        engine_contexts.gui_context
                = gui_context_factory_->Create();
    }

    return engine_contexts;
}

std::shared_ptr<Window> GameFactory::CreateWindow(
        const EngineContexts& engine_contexts){
    if(!window_factory_)
        return nullptr;

    auto window = window_factory_->Create();
    if(!window->Init(engine_contexts.rendering_context,
                     engine_contexts.control_context)){
        throw new std::invalid_argument("window->Init Failed");
    }

    return window;
}

EngineSystems GameFactory::CreateEngineSystems(
        std::shared_ptr<Window> window,
        const EngineContexts& engine_contexts) {
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
        engine_systems.physics_simulation
                = physics_simulation_factory_->Create();
    }
    if (controls_factory_) {
        engine_systems.controls = controls_factory_->Create(
                engine_contexts.control_context);
    }
    if(scene_factory_) {
        engine_systems.scene_container = scene_factory_->Create(
                engine_systems.renderer->scene_renderer(),
                engine_systems.physics_simulation);
    }
    if(gui_factory_) {
        engine_systems.gui = gui_factory_->Create(
                engine_contexts.gui_context);
        engine_systems.gui->Init(window->getHandle(),
                                 engine_contexts.control_context);
    }

    return engine_systems;
}

std::shared_ptr<GameLoop> GameFactory::CreateGameLoop(
        std::shared_ptr<EngineArchitecture> engine_architecture){
    if(game_loop_factory_)
        return game_loop_factory_->Create(engine_architecture);

    return nullptr;
}

}