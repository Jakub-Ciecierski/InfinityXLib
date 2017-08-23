#include "editor/views/factory/soft_body_view_factory.h"

#include "editor/views/soft_body_view.h"

#include <game/factory/game_systems_factory.h>
#include <game/game_updater.h>
#include <game/architecture/engine_architecture.h>

#include <common/unique_ptr.h>

namespace ifx{

SoftBodyViewFactory::SoftBodyViewFactory(
        std::shared_ptr<EngineArchitecture> engine_architecture) :
        engine_architecture_(engine_architecture){}

std::shared_ptr<View> SoftBodyViewFactory::Create(){
    GameSystemsFactory game_systems_factory;
    game_systems_factory.SetGUIFactory(nullptr);
    game_systems_factory.SetControlsFactory(nullptr);

    auto engine_architecture = std::make_shared<EngineArchitecture>();
    engine_architecture->window = engine_architecture_->window;
    engine_architecture->engine_contexts
            = engine_architecture_->engine_contexts;
    engine_architecture->engine_systems = game_systems_factory.Create(
            engine_architecture_->window,
            engine_architecture_->engine_contexts);

    auto game_updater = ifx::make_unique<GameUpdater>(engine_architecture);

    auto soft_body_view = std::make_shared<SoftBodyView>(
            std::move(game_updater));

    return soft_body_view;
}

}
