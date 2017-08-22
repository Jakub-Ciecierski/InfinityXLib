#include "editor/views/factory/soft_body_view_factory.h"

#include "editor/views/soft_body_view.h"

#include <game/factory/game_factory.h>

namespace ifx{

SoftBodyViewFactory::SoftBodyViewFactory(
        std::shared_ptr<GameArchitecture> game_architecture) :
        game_architecture_(game_architecture){}

std::shared_ptr<View> SoftBodyViewFactory::Create(){
    GameFactory game_factory;
    //auto soft_body_view = std::make_shared<SoftBodyView>();
    return nullptr;
}

}
