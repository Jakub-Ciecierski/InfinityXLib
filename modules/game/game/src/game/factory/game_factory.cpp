#include "game/factory/game_factory.h"

#include <game/factory/game_loop_factory.h>
#include <game/game_loop.h>
#include <game/factory/scene_container_factory.h>
#include <game/game.h>
#include <game/scene_container.h>

#include <physics/factory/bullet_physics_simulation_factory.h>

#include <graphics/rendering/renderer.h>
#include <graphics/factory/renderer_factory.h>

namespace ifx {

GameFactory::GameFactory(){
    game_loop_factory_
            = std::shared_ptr<GameLoopFactory>(new GameLoopFactory());
    scene_factory_
            = std::shared_ptr<SceneContainerFactory>(
            new SceneContainerFactory());
    renderer_factory_ = std::shared_ptr<RendererFactory>(new RendererFactory());
    physics_simulation_factory_
            = std::shared_ptr<BulletPhysicsSimulationFactory>(
            new BulletPhysicsSimulationFactory());
}

GameFactory::~GameFactory(){}

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

GameFactory& GameFactory::SetBulletPhysicsSimulationFactory(
        std::shared_ptr<BulletPhysicsSimulationFactory> physics_simulation_factory){
    physics_simulation_factory_ = physics_simulation_factory;
    return *this;
}

std::shared_ptr<Game> GameFactory::Create(){
    auto renderer = renderer_factory_->Create();
    auto physics_simulation = physics_simulation_factory_->Create();

    auto scene = scene_factory_->Create(renderer->scene_renderer(),
                                        physics_simulation);
    auto game_loop = game_loop_factory_->Create(renderer,
                                                physics_simulation,
                                                scene);
    auto game = std::shared_ptr<Game>(new Game(game_loop, scene));
    return game;
}

}