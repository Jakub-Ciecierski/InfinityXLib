#include "engine_gui/factory/engine_gui_factory.h"
#include "game/scene_container.h"

#include <engine_gui/engine_gui.h>
#include <engine_gui/views/main_menu.h>
#include <engine_gui/views/scene_view.h>

namespace ifx {

EngineGUIFactory::EngineGUIFactory(){}

EngineGUIFactory::~EngineGUIFactory(){}

std::shared_ptr<EngineGUI> EngineGUIFactory::CreateEngineGUI(
        std::shared_ptr<SceneContainer> scene){
    EngineGUICreateParams create_params{
            CreateMainMenu(), CreateSceneView(scene)};
    return std::shared_ptr<EngineGUI>(new EngineGUI(create_params));
}

std::shared_ptr<MainMenu> EngineGUIFactory::CreateMainMenu(){
    return std::shared_ptr<MainMenu>(new MainMenu());
}

std::shared_ptr<SceneView> EngineGUIFactory::CreateSceneView(
        std::shared_ptr<SceneContainer> scene){
    return std::shared_ptr<SceneView>(new SceneView(scene));
}

}