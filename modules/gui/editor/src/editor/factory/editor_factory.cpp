#include "editor/factory/editor_factory.h"
#include "game/scene_container.h"

#include <editor/editor.h>
#include <editor/views/main_menu_view.h>
#include <editor/views/scene_view.h>
#include <editor/views/physics_simulation_view.h>
#include <editor/views/imgui_demo_view.h>
#include <game/resources/resource_context.h>
#include <editor/docker.h>
#include <editor/views/bottom_view.h>

namespace ifx {

EditorFactory::EditorFactory(){}

EditorFactory::~EditorFactory(){}

std::shared_ptr<Editor> EditorFactory::CreateEngineGUI(
        std::shared_ptr<Window> window,
        std::shared_ptr<SceneContainer> scene,
        std::shared_ptr<PhysicsSimulation> physics_simulation,
        std::shared_ptr<ResourceContext> resource_creator){
    auto scene_view = CreateSceneView(scene, resource_creator);
    auto physics_simulation_view
            = CreatePhysicsSimulationView(physics_simulation);
    auto imgui_demo_view = std::shared_ptr<ImGuiDemoView>(new ImGuiDemoView());
    auto main_menu_view = std::make_shared<MainMenuView>();
    auto bottom_view = std::make_shared<BottomView>();

    auto docker = CreateDefaultDocker(window, scene_view,
                                      physics_simulation_view,
                                      main_menu_view, bottom_view);

    auto editor = std::make_shared<Editor>(docker);
    editor->AddView(scene_view);
    editor->AddView(physics_simulation_view);
    editor->AddView(main_menu_view);
    editor->AddView(bottom_view);
    editor->AddView(imgui_demo_view);

    main_menu_view->RegisterEditor(editor);

    return editor;
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

std::shared_ptr<Docker> EditorFactory::CreateDefaultDocker(
        std::shared_ptr<Window> window,
        std::shared_ptr<View> scene_view,
        std::shared_ptr<View> physics_view,
        std::shared_ptr<View> main_menu_view,
        std::shared_ptr<View> imgui_demo) {
    auto docker = std::make_shared<Docker>(window);

    docker->RegisterView(scene_view, DockPosition::Left);
    docker->RegisterView(physics_view, DockPosition::Right);
    docker->RegisterView(main_menu_view, DockPosition::Top);
    docker->RegisterView(imgui_demo, DockPosition::Bottom);

    return docker;
}


}