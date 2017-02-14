#include "engine_gui/factory/engine_gui_factory.h"
#include "game/scene_container.h"

#include <engine_gui/engine_gui.h>
#include <engine_gui/views/main_menu.h>
#include <engine_gui/views/scene_view.h>
#include <engine_gui/views/physics_simulation_view.h>

namespace ifx {

EngineGUIFactory::EngineGUIFactory(){}

EngineGUIFactory::~EngineGUIFactory(){}

std::shared_ptr<EngineGUI> EngineGUIFactory::CreateEngineGUI(
        std::shared_ptr<SceneContainer> scene,
        std::shared_ptr<PhysicsSimulation> physics_simulation){
    EngineGUICreateParams create_params{
            CreateMainMenu(),
            CreateSceneView(scene),
            CreatePhysicsSimulationView(physics_simulation)};

    return std::shared_ptr<EngineGUI>(new EngineGUI(create_params));
}

std::shared_ptr<MainMenu> EngineGUIFactory::CreateMainMenu(){
    return std::shared_ptr<MainMenu>(new MainMenu());
}

std::shared_ptr<SceneView> EngineGUIFactory::CreateSceneView(
        std::shared_ptr<SceneContainer> scene){
    return std::shared_ptr<SceneView>(new SceneView(scene));
}

std::shared_ptr<PhysicsSimulationView>
EngineGUIFactory::CreatePhysicsSimulationView(
        std::shared_ptr<PhysicsSimulation> physics_simulation){
    return std::shared_ptr<PhysicsSimulationView>(
            new PhysicsSimulationView(physics_simulation));
}

}