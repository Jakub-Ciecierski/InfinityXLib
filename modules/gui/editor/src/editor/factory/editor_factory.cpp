#include "editor/factory/editor_factory.h"

#include <editor/editor.h>
#include <editor/window_views/main_menu_window_view.h>
#include <editor/views/scene_view.h>
#include <editor/window_views/imgui_demo_window_view.h>
#include <editor/docker.h>
#include <editor/processes/rendering_effect_processor.h>
#include <editor/views/physics_simulation_view.h>
#include <editor/views/rendering_view.h>
#include <editor/views/rendering_views/rendering_effect_view.h>

#include "game/scene_container.h"
#include <game/resources/resource_context.h>

namespace ifx {

EditorFactory::EditorFactory(){}

EditorFactory::~EditorFactory(){}

std::shared_ptr<Editor> EditorFactory::CreateEngineGUI(
        std::shared_ptr<Window> window,
        std::shared_ptr<SceneContainer> scene,
        std::shared_ptr<PhysicsSimulation> physics_simulation,
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator){
    auto left_window_view = CreateLeftWindowView(scene, resource_creator,
                                                 scene_renderer);
    auto right_window_view = CreateRightWindowView(scene_renderer,
                                                   resource_creator,
                                                   physics_simulation);
    auto bottom_window_view = CreateBottomWindowView();
    auto top_window_view = std::make_shared<MainMenuWindowView>();
    auto imgui_demo_view = std::shared_ptr<ImGuiDemoWindowView>(new ImGuiDemoWindowView());
    auto soft_body_window_view = CreateSoftBodyWindowView();

    auto docker = CreateDefaultDocker(window,
                                      left_window_view, right_window_view,
                                      top_window_view, bottom_window_view,
                                      soft_body_window_view);

    auto editor = std::make_shared<Editor>(docker);
    editor->AddWindowView(left_window_view);
    editor->AddWindowView(right_window_view);
    editor->AddWindowView(top_window_view);
    editor->AddWindowView(bottom_window_view);
    editor->AddWindowView(soft_body_window_view);
    editor->AddWindowView(imgui_demo_view);

    top_window_view->RegisterEditor(editor);

    return editor;
}

std::shared_ptr<WindowView> EditorFactory::CreateLeftWindowView(
        std::shared_ptr<SceneContainer> scene,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<SceneRenderer> scene_renderer){
    auto scene_view = CreateSceneView(scene, resource_creator,
                                      scene_renderer);

    return std::make_shared<WindowView>(scene_view, "Left");
}

std::shared_ptr<WindowView> EditorFactory::CreateRightWindowView(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<PhysicsSimulation> physics_simulation){
    auto physics_simulation_view
            = CreatePhysicsSimulationView(physics_simulation);
    auto rendering_view = CreateRenderingView(scene_renderer, resource_creator);

    std::vector<std::shared_ptr<View>> views{physics_simulation_view, rendering_view};

    return std::make_shared<WindowView>(views, "Right");
}

std::shared_ptr<WindowView> EditorFactory::CreateBottomWindowView(){
    return std::make_shared<WindowView>("Bottom");
}

std::shared_ptr<WindowView> EditorFactory::CreateSoftBodyWindowView(){
    auto soft_body_window_view = std::make_shared<WindowView>("Soft Body");
    soft_body_window_view->show(false);

    return soft_body_window_view;
}

std::shared_ptr<SceneView> EditorFactory::CreateSceneView(
        std::shared_ptr<SceneContainer> scene,
        std::shared_ptr<ResourceContext> resource_creator,
        std::shared_ptr<SceneRenderer> scene_renderer){
    return std::make_shared<SceneView>(scene, resource_creator,
                                       scene_renderer);
}

std::shared_ptr<PhysicsSimulationView>
EditorFactory::CreatePhysicsSimulationView(
        std::shared_ptr<PhysicsSimulation> physics_simulation){
    return std::make_shared<PhysicsSimulationView>(physics_simulation);
}

std::shared_ptr<RenderingView> EditorFactory::CreateRenderingView(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<ResourceContext> resource_creator){
    auto rendering_effect_processor
            = std::make_shared<RenderingEffectProcessor>(resource_creator,
                                                         scene_renderer);

    return std::make_shared<RenderingView>(rendering_effect_processor);
}

std::shared_ptr<Docker> EditorFactory::CreateDefaultDocker(
        std::shared_ptr<Window> window,
        std::shared_ptr<WindowView> left_window_view,
        std::shared_ptr<WindowView> right_window_view,
        std::shared_ptr<WindowView> top_window_view,
        std::shared_ptr<WindowView> bottom_window_view,
        std::shared_ptr<WindowView> soft_body_window_view) {
    auto docker = std::make_shared<Docker>(window);

    docker->RegisterView(left_window_view, DockPosition::Left);
    docker->RegisterView(right_window_view, DockPosition::Right);
    docker->RegisterView(top_window_view, DockPosition::Top);
    docker->RegisterView(bottom_window_view, DockPosition::Bottom);
    docker->RegisterView(soft_body_window_view, DockPosition::SoftBody);

    return docker;
}


}