#include "game/factory/scene_container_factory.h"

#include <game/scene_container.h>
#include <graphics/rendering/scene_renderer.h>
//#include <physics/physics_simulation.h>

namespace ifx{

SceneContainerFactory::SceneContainerFactory(){}
SceneContainerFactory::~SceneContainerFactory(){}

std::shared_ptr<SceneContainer> SceneContainerFactory::Create(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<PhysicsSimulation> physics_simulation){
    auto scene = std::shared_ptr<SceneContainer>(
            new SceneContainer(scene_renderer, physics_simulation));
    return scene;
}

}