#include "engine_gui/factory/engine_gui_factory.h"

#include <engine_gui/engine_gui.h>
#include <engine_gui/views/main_menu.h>
#include <engine_gui/views/scene_view.h>

#include <rendering/renderer.h>
#include <rendering/scene/scene.h>

namespace ifx {

EngineGUIFactory::EngineGUIFactory(){}

EngineGUIFactory::~EngineGUIFactory(){}

std::shared_ptr<EngineGUI> EngineGUIFactory::CreateEngineGUI(
        std::shared_ptr<Renderer> renderer){
    EngineGUICreateParams create_params{
            CreateMainMenu(), CreateSceneView(renderer->scene())
    };
    return std::shared_ptr<EngineGUI>(new EngineGUI(create_params));
}

std::shared_ptr<MainMenu> EngineGUIFactory::CreateMainMenu(){
    return std::shared_ptr<MainMenu>(new MainMenu());
}

std::shared_ptr<SceneView> EngineGUIFactory::CreateSceneView(std::shared_ptr<Scene> scene){
    return std::shared_ptr<SceneView>(new SceneView(scene));
}

}