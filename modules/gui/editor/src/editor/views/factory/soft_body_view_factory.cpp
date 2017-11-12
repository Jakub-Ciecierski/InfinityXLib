#include "editor/views/factory/soft_body_view_factory.h"

#include "editor/views/soft_body_view.h"
#include "editor/views/soft_body_views/soft_body_screen_view.h"
#include "editor/views/soft_body_views/soft_body_selector.h"
#include <editor/views/soft_body_views/solver/soft_body_solver_view.h>
#include <editor/views/soft_body_views/boundary_conditions/soft_body_boundary_conditions_view.h>
#include <editor/views/soft_body_views/meshing/soft_body_meshing_view.h>
#include <editor/views/soft_body_views/rendering/soft_body_rendering_view.h>
#include <editor/views/soft_body_views/material/soft_body_material_view.h>
#include <editor/views/soft_body_views/load/soft_body_load_view.h>
#include "editor/views/factory/soft_body_view_factory.h"
#include "editor/views/soft_body_views/meshing/soft_body_meshing_settings_view.h"
#include "editor/views/soft_body_views/meshing/soft_body_meshing_creation_view.h"
#include "editor/views/soft_body_views/meshing/soft_body_meshing_info_view.h"
#include "editor/views/soft_body_views/guide/soft_body_guide_view.h"
#include <editor/views/soft_body_views/picking/ray_casting.h>
#include <editor/views/soft_body_views/picking/box_casting.h>
#include "editor/views/soft_body_views/picking/soft_body_picker.h"
#include "editor/views/soft_body_views/picking/soft_body_node_selection.h"
#include <editor/views/soft_body_views/picking/factory/soft_body_picker_factory.h>
#include <editor/views/soft_body_views/load/traction_force_recorder.h>
#include "editor/views/soft_body_views/solver/dynamic/soft_body_dynamic_solver_view.h"
#include <editor/views/soft_body_views/load/soft_body_load_view_factory.h>

#include "game/resources/resource_context.h"
#include <game/factory/game_systems_factory.h>
#include <game/game_updater.h>
#include <game/game_loop.h>
#include <game/scene_container.h>
#include <game/game_object.h>
#include <game/resources/resource_context.h>
#include <game/architecture/engine_architecture.h>
#include <game/components/cameras/factory/camera_factory.h>
#include <game/components/lights/factory/light_component_factory.h>
#include "game/components/lights/light_directional_component.h"
#include "game/components/cameras/camera_component.h"
#include "game/components/render/render_component.h"

#include <graphics/factory/fbo_renderer_factory.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/model_loader/model_loader.h>

#include <common/unique_ptr.h>

#include <controls/command/factory/command_factory.h>
#include <controls/command/commands/keyboard_command.h>
#include <controls/command/commands/mouse_command.h>
#include <controls/controls.h>
#include <controls/controller/controllers/mouse_controller.h>

#include <math/print_math.h>

#include <iostream>

#include "resources/resource_manager.h"
#include <resources/resources.h>

namespace ifx {

const std::string NODE_RENDERING_EFFECT_NAME = "soft_body_editor/nodes.prog";
const std::string EDGES_RENDERING_EFFECT_NAME = "soft_body_editor/edges.prog";
const std::string FACES_RENDERING_EFFECT_NAME = "soft_body_editor/faces.prog";
const std::string AXIS_RENDERING_EFFECT_NAME = "soft_body_editor/axis.prog";

const std::string AXIS_OBJECT_NAME = "soft_body_editor/axis-obj/axis.obj";

SoftBodyViewFactory::SoftBodyViewFactory(
    std::shared_ptr<GameLoop> game_loop,
    std::shared_ptr<EngineArchitecture> engine_architecture) :
    game_loop_(game_loop),
    engine_architecture_(engine_architecture) {}

std::shared_ptr<View> SoftBodyViewFactory::Create() {
    auto engine_architecture = CreateEngineArchitecture();

    auto soft_body_rendering_effects =
        SetRendererSettings(engine_architecture->engine_systems.renderer,
                            engine_architecture_->engine_systems.renderer);

    auto soft_body_picker = SoftBodyPickerFactory().Create(
        engine_architecture, engine_architecture_);

    auto soft_body_load_view = SoftBodyLoadViewFactory().Create(
        engine_architecture, engine_architecture_, soft_body_picker);

    auto game_updater = ifx::make_unique<GameUpdater>(engine_architecture);
    game_loop_->AddGameUpdater(std::move(game_updater));

    auto soft_body_view = std::make_shared<SoftBodyView>(
        engine_architecture,
        soft_body_rendering_effects,
        soft_body_picker,
        std::move(soft_body_load_view));

    SetDefaultScene(engine_architecture->engine_systems.scene_container,
                    engine_architecture->engine_contexts.resource_context,
                    soft_body_rendering_effects,
                    soft_body_view);

    return soft_body_view;
}

std::shared_ptr<EngineArchitecture>
SoftBodyViewFactory::CreateEngineArchitecture() {
    auto game_systems_factory = CreateGameSystemsFactory();

    auto engine_architecture = std::make_shared<EngineArchitecture>();
    engine_architecture->window = engine_architecture_->window;
    engine_architecture->engine_contexts
        = engine_architecture_->engine_contexts;
    engine_architecture->engine_systems = game_systems_factory->Create(
        engine_architecture_->window,
        engine_architecture_->engine_contexts);
    engine_architecture->window = nullptr;

    return engine_architecture;
}

std::unique_ptr<GameSystemsFactory>
SoftBodyViewFactory::CreateGameSystemsFactory() {
    auto game_systems_factory = ifx::make_unique<GameSystemsFactory>();

    game_systems_factory->SetGUIFactory(nullptr);
    game_systems_factory->SetControlsFactory(nullptr);
    game_systems_factory->SetRendererFactory(
        std::make_shared<FBORendererFactory>());

    return game_systems_factory;
}

SoftBodyRenderingEffects SoftBodyViewFactory::SetRendererSettings(
    std::shared_ptr<Renderer> renderer,
    std::shared_ptr<Renderer> old_renderer) {
    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(renderer);
    fbo_renderer->EnableRenderToScreen(false);

    auto soft_body_rendering_effects = CreateRenderingEffects(old_renderer);
    soft_body_rendering_effects.main->rendering_state().drawing_priority = 2;
    soft_body_rendering_effects.main->enabled(false);
    soft_body_rendering_effects.faces->rendering_state().drawing_priority = 1;
    soft_body_rendering_effects.edges->rendering_state().drawing_priority = 3;
    soft_body_rendering_effects.nodes->rendering_state().drawing_priority = 4;

    renderer->scene_renderer()->Add(soft_body_rendering_effects.main);
    renderer->scene_renderer()->Add(soft_body_rendering_effects.nodes);
    renderer->scene_renderer()->Add(soft_body_rendering_effects.edges);
    renderer->scene_renderer()->Add(soft_body_rendering_effects.faces);
    renderer->scene_renderer()->Add(soft_body_rendering_effects.axis);

    return soft_body_rendering_effects;
}

SoftBodyRenderingEffects SoftBodyViewFactory::CreateRenderingEffects(
    std::shared_ptr<Renderer> old_renderer) {
    SoftBodyRenderingEffects soft_body_rendering_effects;
    soft_body_rendering_effects.main =
        std::make_shared<RenderingEffect>(
            *old_renderer->scene_renderer()->
                default_rendering_effect());

    auto &rendering_effects =
        old_renderer->scene_renderer()->rendering_effects();
    for (auto &rendering_effect : rendering_effects) {
        if (rendering_effect->name() == NODE_RENDERING_EFFECT_NAME) {
            soft_body_rendering_effects.nodes =
                std::make_shared<RenderingEffect>(*rendering_effect);
        } else if (rendering_effect->name() == EDGES_RENDERING_EFFECT_NAME) {
            soft_body_rendering_effects.edges =
                std::make_shared<RenderingEffect>(*rendering_effect);
        } else if (rendering_effect->name() == FACES_RENDERING_EFFECT_NAME) {
            soft_body_rendering_effects.faces =
                std::make_shared<RenderingEffect>(*rendering_effect);
        } else if (rendering_effect->name() == AXIS_RENDERING_EFFECT_NAME){
            soft_body_rendering_effects.axis =
                std::make_shared<RenderingEffect>(*rendering_effect);
        }
    }

    if (!soft_body_rendering_effects.main
        || !soft_body_rendering_effects.nodes
        || !soft_body_rendering_effects.edges
        || !soft_body_rendering_effects.faces
        || !soft_body_rendering_effects.axis) {
        throw std::invalid_argument("SoftBodyRenderingEffects not found");
    }

    return soft_body_rendering_effects;
}

void SoftBodyViewFactory::SetDefaultScene(
    std::shared_ptr<SceneContainer> scene,
    std::shared_ptr<ResourceContext> resource_context,
    SoftBodyRenderingEffects& rendering_effects,
    std::shared_ptr<SoftBodyView> soft_body_view) {
    // Camera
    auto game_object = scene->CreateAndAddEmptyGameObject();
    auto camera = CameraFactory().CreateCamera(
        engine_architecture_->window.get());
    camera->camera_style(CameraStyle::ThirdPerson);
    camera->moveTo(glm::vec3(0, 0, 0));
    camera->rotateTo(glm::vec3(0, 0, 0));
    camera->scale(5);
    camera->SetWorldUp(glm::vec3(0, -1, 0));

    game_object->Add(std::dynamic_pointer_cast<GameComponent>(camera));
    soft_body_view->screen_view().SetCamera(camera);

    SetKeybinds(engine_architecture_->engine_systems.controls,
                camera,
                soft_body_view);

    // Lights
    auto light_game_object = scene->CreateAndAddEmptyGameObject();
    light_game_object->Add(
        LightComponentFactory().CreateDirectionalLight(
            engine_architecture_->engine_contexts.resource_context->
                texture_creator(),
            engine_architecture_->engine_contexts.resource_context->
                program_creator()));
    light_game_object->rotateTo(glm::vec3(50, -50, 0));
    light_game_object->moveTo(glm::vec3(0, 10, 0));

    // Axis
    auto axis_game_object = scene->CreateAndAddEmptyGameObject();
    auto axis_render_component = CreateAxis(resource_context);
    axis_game_object->Add(axis_render_component);
    rendering_effects.axis->RegisterRenderObject(axis_render_component);
}

std::shared_ptr<RenderComponent> SoftBodyViewFactory::CreateAxis(
    std::shared_ptr<ResourceContext> resource_context){
    auto asset_name = resource_context->resource_manager()->resource_path()
        ->GetResourcePath(AXIS_OBJECT_NAME, ResourceType::MODEL);
    ModelLoader model_loader(asset_name,
                             resource_context->model_creator(),
                             resource_context->texture_creator());
    auto model = model_loader.loadModel();

    return std::make_shared<RenderComponent>(model);
}

void SoftBodyViewFactory::SetKeybinds(
    std::shared_ptr<ifx::Controls> controls,
    std::shared_ptr<ifx::CameraComponent> camera,
    std::shared_ptr<SoftBodyView> soft_body_view) {
    auto command_factory = ifx::CommandFactory(controls);

    auto command_q = command_factory.CreateKeyboardCommand(
        nullptr,
        [soft_body_view](std::shared_ptr<ifx::Controller> controller,
                         std::shared_ptr<ifx::Controlable> obj){
            soft_body_view->soft_body_views_selection().selected = 1;
        },
        KeyboardControllerEventType{
            KeyboardControllerKeyType::Q,
            KeyboardControllerCallbackType::PRESSED
        }
    );
    auto command_w = command_factory.CreateKeyboardCommand(
        nullptr,
        [soft_body_view](std::shared_ptr<ifx::Controller> controller,
                         std::shared_ptr<ifx::Controlable> obj){
            soft_body_view->soft_body_views_selection().selected = 2;
        },
        KeyboardControllerEventType{
            KeyboardControllerKeyType::W,
            KeyboardControllerCallbackType::PRESSED
        }
    );
    auto command_e = command_factory.CreateKeyboardCommand(
        nullptr,
        [soft_body_view](std::shared_ptr<ifx::Controller> controller,
                         std::shared_ptr<ifx::Controlable> obj){
            soft_body_view->soft_body_views_selection().selected = 3;
        },
        KeyboardControllerEventType{
            KeyboardControllerKeyType::E,
            KeyboardControllerCallbackType::PRESSED
        }
    );
    auto command_r = command_factory.CreateKeyboardCommand(
        nullptr,
        [soft_body_view](std::shared_ptr<ifx::Controller> controller,
                         std::shared_ptr<ifx::Controlable> obj){
            soft_body_view->soft_body_views_selection().selected = 4;
        },
        KeyboardControllerEventType{
            KeyboardControllerKeyType::R,
            KeyboardControllerCallbackType::PRESSED
        }
    );
    auto command_t = command_factory.CreateKeyboardCommand(
        nullptr,
        [soft_body_view](std::shared_ptr<ifx::Controller> controller,
                         std::shared_ptr<ifx::Controlable> obj){
            soft_body_view->soft_body_views_selection().selected = 5;
        },
        KeyboardControllerEventType{
            KeyboardControllerKeyType::T,
            KeyboardControllerCallbackType::PRESSED
        }
    );
    auto command_y = command_factory.CreateKeyboardCommand(
        nullptr,
        [soft_body_view](std::shared_ptr<ifx::Controller> controller,
                         std::shared_ptr<ifx::Controlable> obj){
            soft_body_view->soft_body_views_selection().selected = 6;
        },
        KeyboardControllerEventType{
            KeyboardControllerKeyType::Y,
            KeyboardControllerCallbackType::PRESSED
        }
    );

    auto command_rotate_mouse = command_factory.CreateMouseCommand(
        camera,
        [soft_body_view](
            std::shared_ptr<ifx::Controller> controller,
            std::shared_ptr<ifx::Controlable> obj) {
            if (!soft_body_view->is_window_focused())
                return;

            auto mouse = std::static_pointer_cast<ifx::MouseController>(
                controller);
            auto camera = std::static_pointer_cast<ifx::CameraComponent>
                (obj);
            auto current_position = mouse->GetCurrentPosition();
            auto previous_position = mouse->GetPreviousPosition();

            float xoffset = current_position.x - previous_position.x;
            float yoffset = previous_position.y - current_position.y;

            float rotationSpeed = 0.1f;
            camera->rotate(glm::vec3(-xoffset * rotationSpeed,
                                     yoffset * rotationSpeed,
                                     0));
        },
        ifx::MouseControllerEventType {
            ifx::MouseControllerKeyType::MOUSE_RIGHT,
            ifx::MouseControllerCallbackType::PRESSED
        }
    );

    auto command_scroll = command_factory.CreateMouseCommand(
        camera,
        [soft_body_view](
            std::shared_ptr<ifx::Controller> controller,
            std::shared_ptr<ifx::Controlable> obj) {
            if (!soft_body_view->is_window_focused())
                return;
            auto mouse = std::static_pointer_cast<ifx::MouseController>(
                controller);
            auto camera = std::static_pointer_cast<ifx::CameraComponent>
                (obj);

            auto current_scale = camera->getScale();
            auto offset = (0.5f * mouse->GetScrollOffset().y);
            if (current_scale.x < 0 && offset < 0)
                offset = 0;
            camera->scale(current_scale + offset);
        },
        ifx::MouseControllerEventType {
            ifx::MouseControllerKeyType::MOUSE_SCROLL,
            ifx::MouseControllerCallbackType::SCROLL_ACTIVE
        }
    );
    auto command_middle = command_factory.CreateMouseCommand(
        camera,
        [](std::shared_ptr<ifx::Controller> controller,
           std::shared_ptr<ifx::Controlable> obj) {
            auto mouse = std::static_pointer_cast<ifx::MouseController>(
                controller);
            auto camera = std::static_pointer_cast<ifx::CameraComponent>
                (obj);
            float movementSpeed = 0.1f;

            auto current_position = mouse->GetCurrentPosition();
            auto previous_position = mouse->GetPreviousPosition();

            float xoffset = current_position.x - previous_position.x;
            float yoffset = previous_position.y - current_position.y;

            camera->move(-xoffset * camera->GetRight() *
                movementSpeed * 0.1f);
            camera->move(yoffset * camera->GetUp() *
                movementSpeed * 0.1f);
        },
        ifx::MouseControllerEventType {
            ifx::MouseControllerKeyType::MOUSE_MIDDLE,
            ifx::MouseControllerCallbackType::PRESSED
        }
    );
    auto command_zoom = command_factory.CreateMouseCommand(
        camera,
        [soft_body_view](
            std::shared_ptr<ifx::Controller> controller,
            std::shared_ptr<ifx::Controlable> obj) {
            if (!soft_body_view->is_window_focused())
                return;
            auto mouse = std::static_pointer_cast<ifx::MouseController>(
                controller);
            auto camera = std::static_pointer_cast<ifx::CameraComponent>
                (obj);
            float movementSpeed = 0.1f;

            auto current_position = mouse->GetCurrentPosition();
            auto previous_position = mouse->GetPreviousPosition();

            float yoffset = previous_position.y - current_position.y;

            auto current_scale = camera->getScale();
            camera->scale(current_scale + (0.1f * movementSpeed * yoffset));
        },
        ifx::MouseControllerEventType {
            ifx::MouseControllerKeyType::MOUSE_RIGHT,
            ifx::MouseControllerCallbackType::PRESSED
        }
    );

    controls->AddCommand(command_q);
    controls->AddCommand(command_w);
    controls->AddCommand(command_e);
    controls->AddCommand(command_r);
    controls->AddCommand(command_t);
    controls->AddCommand(command_y);
    controls->AddCommand(command_middle);
    controls->AddCommand(command_rotate_mouse);
    controls->AddCommand(command_scroll);
}

}
