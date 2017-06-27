#include "editor/factory/editor_factory.h"
#include "game/scene_container.h"

#include <editor/editor.h>
#include <editor/views/main_menu.h>
#include <editor/views/scene_view.h>
#include <editor/views/physics_simulation_view.h>
#include <editor/views/imgui_demo_view.h>
#include <game/resources/resource_context.h>

namespace ifx {

EditorFactory::EditorFactory(){}

EditorFactory::~EditorFactory(){}

std::shared_ptr<Editor> EditorFactory::CreateEngineGUI(
        std::shared_ptr<SceneContainer> scene,
        std::shared_ptr<PhysicsSimulation> physics_simulation,
        std::shared_ptr<ResourceContext> resource_creator){
    auto scene_view = CreateSceneView(scene, resource_creator);
    auto physics_simulation_view
            = CreatePhysicsSimulationView(physics_simulation);
    auto imgui_demo_view = std::shared_ptr<ImGuiDemoView>(new ImGuiDemoView());
    auto main_menu = CreateMainMenu(scene_view,
                                    physics_simulation_view,
                                    imgui_demo_view);

    EngineGUICreateParams create_params{main_menu,
                                        scene_view,
                                        physics_simulation_view,
                                        imgui_demo_view};

    return std::shared_ptr<Editor>(new Editor(create_params));
}

std::shared_ptr<SceneView> EditorFactory::CreateSceneView(
        std::shared_ptr<SceneContainer> scene,
        std::shared_ptr<ResourceContext> resource_creator){
    return std::shared_ptr<SceneView>(new SceneView(scene, resource_creator));
}

std::shared_ptr<PhysicsSimulationView>
EditorFactory::CreatePhysicsSimulationView(
        std::shared_ptr<PhysicsSimulation> physics_simulation){
    return std::shared_ptr<PhysicsSimulationView>(
            new PhysicsSimulationView(physics_simulation));
}

std::shared_ptr<MainMenu> EditorFactory::CreateMainMenu(
        std::shared_ptr<SceneView> scene_view,
        std::shared_ptr<PhysicsSimulationView> physics_simulation_view,
        std::shared_ptr<ImGuiDemoView> imgui_demo_view){
    return std::shared_ptr<MainMenu>(new MainMenu(
            scene_view, physics_simulation_view, imgui_demo_view));
}

}