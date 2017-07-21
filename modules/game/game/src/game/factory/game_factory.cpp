#include "game/factory/game_factory.h"

#include <game/factory/game_loop_factory.h>
#include <game/game_loop.h>
#include <game/factory/scene_container_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <game/resources/factory/resource_context_factory.h>

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

//#include <engine_gui/

namespace ifx {

GameFactory::GameFactory(){
    CreateDefaultFactories();
}

GameFactory::~GameFactory(){}

void GameFactory::CreateDefaultFactories(){
    window_factory_ = std::shared_ptr<WindowFactory>(new WindowFactory());

    rendering_context_factory_ = std::shared_ptr<RenderingContextOpenglFactory>(
            new RenderingContextOpenglFactory());

    resource_context_factory_ = std::shared_ptr<ResourceContextFactory>(
            new ResourceContextFactory());

    game_loop_factory_
            = std::shared_ptr<GameLoopFactory>(new GameLoopFactory());

    scene_factory_ = std::shared_ptr<SceneContainerFactory>(
            new SceneContainerFactory());

    renderer_factory_ = std::shared_ptr<RendererFactory>(new RendererFactory());

    physics_simulation_factory_ =
            std::shared_ptr<BulletPhysicsSimulationFactory>(
                    new BulletPhysicsSimulationFactory());

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
    auto rendering_context = rendering_context_factory_->Create();
    auto resource_context = resource_context_factory_->Create();
    auto control_context = control_context_factory_->Create();
    auto gui_context = gui_context_factory_->Create();

    auto window = window_factory_->Create();
    if(!window->Init(rendering_context, control_context))
        throw new std::invalid_argument("window->Init Failed");

    auto renderer = renderer_factory_->Create(window,
                                              rendering_context);
    auto physics_simulation = physics_simulation_factory_->Create();
    auto controls = controls_factory_->Create(control_context);

    auto scene = scene_factory_->Create(renderer->scene_renderer(),
                                        physics_simulation);

    auto gui = gui_factory_->Create(gui_context);
    gui->Init(window->getHandle(), control_context);

    auto game_loop = game_loop_factory_->Create(renderer,
                                                physics_simulation,
                                                controls,
                                                scene,
                                                gui);

    auto game = std::shared_ptr<Game>(new Game(game_loop,
                                               scene,
                                               resource_context,
                                               rendering_context));
    return game;
}




}