#include "game/game.h"

#include <game/game_loop.h>

namespace ifx{

Game::Game(std::shared_ptr<GameLoop> game_loop,
           std::shared_ptr<SceneContainer> scene) :
        game_loop_(game_loop),
        scene_(scene){}

Game::~Game(){}

void Game::Start(){
    game_loop_->Start();
}


}