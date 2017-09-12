#include "editor/factory/editor_factory.h"

#include <editor/editor.h>
#include <editor/window_views/main_menu_window_view.h>
#include <editor/views/scene_list_view.h>
#include <editor/window_views/imgui_demo_window_view.h>
#include <editor/docker.h>
#include <editor/processes/rendering_effect_processor.h>
#include <editor/views/physics_simulation_view.h>
#include <editor/views/rendering_view.h>
#include <editor/views/rendering_views/rendering_effect_view.h>
#include <editor/views/factory/soft_body_view_factory.h>
#include <editor/views/scene_views/game_object_view.h>
#include <editor/views/scene_views/game_component_view.h>
#include <editor/views/scene_views/scene_manipulator_view.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu.h>
#include <editor/views/scene_views/context_menus/game_component_context_menu.h>
#include <editor/views/scene_views/context_menus/scene_list_context_menu.h>
#include "editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object.h"
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_parametric_equation.h>
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_render_object/context_menu_add_render_object_asset.h>
#include "editor/views/scene_views/movable_object_view.h"
#include "editor/views/scene_views/game_component_views/camera_view.h"
#include "editor/views/scene_views/game_component_views/light_view.h"
#include "editor/views/scene_views/game_component_views/render_object_view.h"
#include <editor/views/scene_views/context_menus/game_object_context_menu/context_menu_add_light.h>
#include "editor/views/soft_body_view.h"
#include "editor/views/scene_view.h"
#include <editor/window_views/screen_window_view.h>

#include "game/scene_container.h"
#include <game/architecture/engine_architecture.h>
#include <game/resources/resource_context.h>

#include "graphics/model_loader/parametric_loader/parametric_interpreter.h"
#include <graphics/rendering/renderer.h>

namespace ifx {

std::shared_ptr<Editor> EditorFactory::CreateEngineGUI(
    std::shared_ptr<EngineArchitecture> engine_architecture) {
    // Create Views
    auto scene_view = std::make_shared<SceneView>();
    auto scene_list_view = CreateSceneView(
        engine_architecture->engine_systems.scene_container,
        engine_architecture->engine_contexts.resource_context,
        engine_architecture->engine_systems.renderer->scene_renderer());
    auto physics_simulation_view = CreatePhysicsSimulationView(
        engine_architecture->engine_systems.physics_simulation);
    auto rendering_view = CreateRenderingView(
        engine_architecture->engine_systems.renderer->scene_renderer(),
        engine_architecture->engine_contexts.resource_context);
    auto soft_body_view = CreateSoftBodyView(engine_architecture);
    scene_list_view->AddObserver(soft_body_view);

    // Create Window views
    auto left_window_view =
        std::make_shared<WindowView>(scene_list_view, "Left");

    std::vector<std::shared_ptr<View>>
        views{physics_simulation_view, rendering_view};
    auto right_window_view = std::make_shared<WindowView>(views, "Right");

    auto bottom_window_view = std::make_shared<WindowView>("Bottom");

    auto top_window_view = std::make_shared<MainMenuWindowView>();

    auto imgui_demo_view = std::make_shared<ImGuiDemoWindowView>();

    auto middle_screen_window_view = std::make_shared<ScreenWindowView>(
        scene_view, soft_body_view);

    // Docker
    auto docker = CreateDefaultDocker(engine_architecture->window,
                                      left_window_view, right_window_view,
                                      top_window_view, bottom_window_view,
                                      middle_screen_window_view);

    auto editor = std::make_shared<Editor>(docker);
    editor->AddWindowView(left_window_view);
    editor->AddWindowView(right_window_view);
    editor->AddWindowView(top_window_view);
    editor->AddWindowView(bottom_window_view);
    editor->AddWindowView(middle_screen_window_view);
    editor->AddWindowView(imgui_demo_view);

    top_window_view->RegisterEditor(editor);

    return editor;
}

std::shared_ptr<SceneListView> EditorFactory::CreateSceneView(
    std::shared_ptr<SceneContainer> scene,
    std::shared_ptr<ResourceContext> resource_creator,
    std::shared_ptr<SceneRenderer> scene_renderer) {
    return std::make_shared<SceneListView>(scene, resource_creator,
                                           scene_renderer);
}

std::shared_ptr<PhysicsSimulationView>
EditorFactory::CreatePhysicsSimulationView(
    std::shared_ptr<PhysicsSimulation> physics_simulation) {
    return std::make_shared<PhysicsSimulationView>(physics_simulation);
}

std::shared_ptr<RenderingView> EditorFactory::CreateRenderingView(
    std::shared_ptr<SceneRenderer> scene_renderer,
    std::shared_ptr<ResourceContext> resource_creator) {
    auto rendering_effect_processor
        = std::make_shared<RenderingEffectProcessor>(resource_creator,
                                                     scene_renderer);

    return std::make_shared<RenderingView>(rendering_effect_processor);
}

std::shared_ptr<SoftBodyView> EditorFactory::CreateSoftBodyView(
    std::shared_ptr<EngineArchitecture> engine_architecture) {
    return std::dynamic_pointer_cast<SoftBodyView>(
        SoftBodyViewFactory(engine_architecture).Create());
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