#include "game/game.h"

#include <game/game_loop.h>

#include <graphics/rendering/context/rendering_context.h>

#include "gui/context/gui_context.h"
#include "gui/gui.h"

#include "controls/context/control_context.h"

#include <physics/context/physics_context.h>
#include <physics/physics_simulation.h>

namespace ifx{

Game::Game(std::shared_ptr<GameLoop> game_loop,
           std::shared_ptr<EngineArchitecture> engine_architecture) :
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
    TerminateSystems();
    TerminateContexts();
}

void Game::TerminateSystems(){
    engine_architecture_->engine_systems.gui->Terminate();
    engine_architecture_->engine_systems.physics_simulation->Terminate();
}

void Game::TerminateContexts(){
    engine_architecture_->engine_contexts.rendering_context->Terminate();
    engine_architecture_->engine_contexts.control_context->Terminate();
    engine_architecture_->engine_contexts.gui_context->Terminate();
    engine_architecture_->engine_contexts.physics_context->Terminate();
}

}