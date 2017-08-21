#include "game/game.h"

#include <game/game_loop.h>

#include <graphics/rendering/context/rendering_context.h>

#include "gui/context/gui_context.h"

#include "controls/context/control_context.h"

namespace ifx{

Game::Game(std::shared_ptr<GameLoop> game_loop,
           const EngineArchitecture& engine_architecture) :
        game_loop_(game_loop),
        engine_architecture_(engine_architecture){
    if(!game_loop){
        throw std::invalid_argument("Game::Game() - Requires GameLoop");
    }
}

void Game::Start(){
    game_loop_->Start();

    Terminate();
}

void Game::Terminate(){
    engine_architecture_.engine_contexts.rendering_context->Terminate();
    engine_architecture_.engine_contexts.control_context->Terminate();
    engine_architecture_.engine_contexts.gui_context->Terminate();
}

}