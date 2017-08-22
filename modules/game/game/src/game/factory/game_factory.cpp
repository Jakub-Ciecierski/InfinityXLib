#include "game/factory/game_factory.h"

#include <game/factory/game_loop_factory.h>
#include <game/game_loop.h>
#include <game/game.h>
#include <game/factory/game_contexts_factory.h>
#include <game/factory/game_systems_factory.h>

#include <graphics/rendering/window/window.h>
#include <graphics/rendering/renderer.h>

#include <graphics/factory/renderer_factory.h>
#include <graphics/rendering/window/factory/window_factory.h>

namespace ifx {

GameFactory::GameFactory(){
    CreateDefaultFactories();
}

void GameFactory::CreateDefaultFactories(){
    game_contexts_factory_ = std::make_shared<GameContextsFactory>();
    game_systems_factory_ = std::make_shared<GameSystemsFactory>();
    window_factory_ = std::make_shared<WindowFactory>();
    game_loop_factory_ = std::make_shared<GameLoopFactory>();
}

GameFactory&
GameFactory::SetGameContextsFactory(
        std::shared_ptr<GameContextsFactory> factory){
    game_contexts_factory_ = factory;
    return *this;
}
GameFactory&
GameFactory::SetGameSystemsFactory(
        std::shared_ptr<GameSystemsFactory> factory){
    game_systems_factory_ = factory;
    return *this;
}

GameFactory& GameFactory::SetWindowFactory(
        std::shared_ptr<WindowFactory> factory){
    window_factory_ = factory;
    return *this;
}

GameFactory& GameFactory::SetGameLoopFactory(
        std::shared_ptr<GameLoopFactory> game_loop_factory){
    game_loop_factory_ = game_loop_factory;
    return *this;
}

std::shared_ptr<Game> GameFactory::Create(){
    auto engine_architecture = CreateEngineArchitecture();

    if(!game_loop_factory_)
        throw std::invalid_argument("game_loop_factory_ nullptr");
    auto game_loop = game_loop_factory_->Create(engine_architecture);

    auto game = std::make_shared<Game>(game_loop, engine_architecture);

    return game;
}

std::shared_ptr<EngineArchitecture> GameFactory::CreateEngineArchitecture(){
    auto engine_architecture = std::make_shared<EngineArchitecture>();

    if(!game_systems_factory_ || !game_contexts_factory_ || !window_factory_){
        throw std::invalid_argument("CreateEngineArchitecture factory nullptr");
    }

    engine_architecture->engine_contexts = game_contexts_factory_->Create();
    engine_architecture->window = window_factory_->Create(
            engine_architecture->engine_contexts.rendering_context,
            engine_architecture->engine_contexts.control_context);
    engine_architecture->engine_systems = game_systems_factory_->Create(
            engine_architecture->window,
            engine_architecture->engine_contexts);

    return engine_architecture;
}

}