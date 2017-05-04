#include "game/game.h"

#include <game/game_loop.h>
#include <game/resources/resource_context.h>
#include <graphics/rendering/context/rendering_context.h>

namespace ifx{

Game::Game(std::shared_ptr<GameLoop> game_loop,
           std::shared_ptr<SceneContainer> scene,
           std::shared_ptr<ResourceContext> resource_creator,
           std::shared_ptr<RenderingContext> rendering_context) :
        game_loop_(game_loop),
        scene_(scene),
        resource_creator_(resource_creator),
        rendering_context_(rendering_context){}

Game::~Game(){}

void Game::Start(){
    game_loop_->Start();

    Terminate();
}

void Game::Terminate(){
    rendering_context_->Terminate();

    // other context termination
}

}