#include "editor/views/factory/soft_body_view_factory.h"

#include "editor/views/soft_body_view.h"

#include <game/factory/game_systems_factory.h>
#include <game/game_updater.h>
#include <game/scene_container.h>
#include <game/game_object.h>
#include <game/resources/resource_context.h>
#include <game/architecture/engine_architecture.h>
#include <game/components/cameras/factory/camera_factory.h>
#include <game/components/lights/factory/light_component_factory.h>
#include "game/components/lights/light_directional_component.h"
#include "game/components/cameras/camera_component.h"

#include <graphics/factory/fbo_renderer_factory.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>

#include <common/unique_ptr.h>

#include <controls/command/factory/command_factory.h>
#include <controls/command/commands/keyboard_command.h>
#include <controls/command/commands/mouse_command.h>
#include <controls/controls.h>
#include <controls/controller/controllers/mouse_controller.h>
#include <math/print_math.h>

namespace ifx{

SoftBodyViewFactory::SoftBodyViewFactory(
        std::shared_ptr<EngineArchitecture> engine_architecture) :
        engine_architecture_(engine_architecture){}

std::shared_ptr<View> SoftBodyViewFactory::Create(){
    auto engine_architecture = CreateEngineArchitecture();

    SetRendererSettings(engine_architecture->engine_systems.renderer,
                        engine_architecture_->engine_systems.renderer);
    SetDefaultScene(engine_architecture ->engine_systems.scene_container);

    auto game_updater = ifx::make_unique<GameUpdater>(engine_architecture);
    auto soft_body_view = std::make_shared<SoftBodyView>(
            std::move(game_updater));

    return soft_body_view;
}

std::shared_ptr<EngineArchitecture>
SoftBodyViewFactory::CreateEngineArchitecture(){
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
SoftBodyViewFactory::CreateGameSystemsFactory(){
    auto game_systems_factory = ifx::make_unique<GameSystemsFactory>();

    game_systems_factory->SetGUIFactory(nullptr);
    game_systems_factory->SetControlsFactory(nullptr);
    game_systems_factory->SetRendererFactory(
            std::make_shared<FBORendererFactory>());

    return game_systems_factory;
}

void SoftBodyViewFactory::SetDefaultScene(
        std::shared_ptr<SceneContainer> scene){
    // Camera
    auto game_object = scene->CreateAndAddEmptyGameObject();
    auto camera = CameraFactory().CreateCamera(
            engine_architecture_->window.get());
    camera->camera_style(CameraStyle::ThirdPerson);
    camera->moveTo(glm::vec3(0,0,0));
    camera->rotateTo(glm::vec3(0,0,0));
    camera->scale(5);

    game_object->Add(std::dynamic_pointer_cast<GameComponent>(camera));
    SetKeybinds(engine_architecture_->engine_systems.controls, camera);

    // Lights
    auto light_game_object = scene->CreateAndAddEmptyGameObject();
    light_game_object->Add(
            LightComponentFactory().CreateDirectionalLight(
                    engine_architecture_->engine_contexts.resource_context->
                            texture_creator(),
                    engine_architecture_->engine_contexts.resource_context->
                            program_creator()));
    light_game_object->rotateTo(glm::vec3(50, -50, 0));
    light_game_object->moveTo(glm::vec3(0,10,0));
}

void SoftBodyViewFactory::SetRendererSettings(
        std::shared_ptr<Renderer> renderer,
        std::shared_ptr<Renderer> old_renderer){
    auto fbo_renderer = std::dynamic_pointer_cast<FBORenderer>(renderer);
    fbo_renderer->EnableRenderToScreen(false);

    auto old_default_rendering_effect
            = old_renderer->scene_renderer()->default_rendering_effect();
    auto new_default_rendering_effect = std::make_shared<RenderingEffect>(
            *old_default_rendering_effect);

    renderer->scene_renderer()->Add(new_default_rendering_effect);
    renderer->scene_renderer()->SetDefaultRenderingEffect(
            new_default_rendering_effect);
}

void SoftBodyViewFactory::SetKeybinds(
        std::shared_ptr<ifx::Controls> controls,
        std::shared_ptr<ifx::CameraComponent> camera){
    auto command_factory = ifx::CommandFactory(controls);

    auto command_left = command_factory.CreateKeyboardCommand(
            camera,
            [](std::shared_ptr<ifx::Controller>,
               std::shared_ptr<ifx::Controlable> obj){
                float movementSpeed = 0.1f;
                std::static_pointer_cast<ifx::CameraComponent>(obj)->
                        moveLeft(movementSpeed);
            },
            ifx::KeyboardControllerEventType {
                    ifx::KeyboardControllerKeyType::A,
                    ifx::KeyboardControllerCallbackType::PRESSED
            }
    );

    auto command_right = command_factory.CreateKeyboardCommand(
            camera,
            [](std::shared_ptr<ifx::Controller>,
               std::shared_ptr<ifx::Controlable> obj){
                float movementSpeed = 0.1f;
                std::static_pointer_cast<ifx::CameraComponent>(obj)->
                        moveRight(movementSpeed);
            },
            ifx::KeyboardControllerEventType {
                    ifx::KeyboardControllerKeyType::D,
                    ifx::KeyboardControllerCallbackType::PRESSED
            }
    );

    auto command_forward = command_factory.CreateKeyboardCommand(
            camera,
            [](std::shared_ptr<ifx::Controller>,
               std::shared_ptr<ifx::Controlable> obj){
                float movementSpeed = 0.1f;
                std::static_pointer_cast<ifx::CameraComponent>(obj)->
                        moveForward(movementSpeed);
            },
            ifx::KeyboardControllerEventType {
                    ifx::KeyboardControllerKeyType::W,
                    ifx::KeyboardControllerCallbackType::PRESSED
            }
    );

    auto command_backwards = command_factory.CreateKeyboardCommand(
            camera,
            [](std::shared_ptr<ifx::Controller>,
               std::shared_ptr<ifx::Controlable> obj){
                float movementSpeed = 0.1f;
                std::static_pointer_cast<ifx::CameraComponent>(obj)->
                        moveBackward(movementSpeed);
            },
            ifx::KeyboardControllerEventType {
                    ifx::KeyboardControllerKeyType::S,
                    ifx::KeyboardControllerCallbackType::PRESSED
            }
    );

    auto command_down = command_factory.CreateKeyboardCommand(
            camera,
            [](std::shared_ptr<ifx::Controller>,
               std::shared_ptr<ifx::Controlable> obj){
                float movementSpeed = 0.1f;
                std::static_pointer_cast<ifx::CameraComponent>(obj)->
                        moveDown(movementSpeed);
            },
            ifx::KeyboardControllerEventType {
                    ifx::KeyboardControllerKeyType::E,
                    ifx::KeyboardControllerCallbackType::PRESSED
            }
    );

    auto command_up = command_factory.CreateKeyboardCommand(
            camera,
            [](std::shared_ptr<ifx::Controller>,
               std::shared_ptr<ifx::Controlable> obj){
                float movementSpeed = 0.1f;
                std::static_pointer_cast<ifx::CameraComponent>(obj)->
                        moveUp(movementSpeed);
            },
            ifx::KeyboardControllerEventType {
                    ifx::KeyboardControllerKeyType::Q,
                    ifx::KeyboardControllerCallbackType::PRESSED
            }
    );

    auto command_rotate_mouse = command_factory.CreateMouseCommand(
            camera,
            [](std::shared_ptr<ifx::Controller> controller,
               std::shared_ptr<ifx::Controlable> obj){
                auto mouse = std::static_pointer_cast<ifx::MouseController>(
                        controller);
                auto camera = std::static_pointer_cast<ifx::CameraComponent>
                        (obj);
                auto current_position = mouse->GetCurrentPosition();
                auto previous_position = mouse->GetPreviousPosition();

                float xoffset = current_position.x - previous_position.x;
                float yoffset = previous_position.y - current_position.y;

                float rotationSpeed = 0.1f;
                camera->rotate(glm::vec3(xoffset * rotationSpeed,
                                         yoffset * rotationSpeed, 0));
            },
            ifx::MouseControllerEventType {
                    ifx::MouseControllerKeyType::MOUSE_RIGHT,
                    ifx::MouseControllerCallbackType::PRESSED
            }
    );

    auto command_scroll = command_factory.CreateMouseCommand(
            camera,
            [](std::shared_ptr<ifx::Controller> controller,
               std::shared_ptr<ifx::Controlable> obj){
                auto mouse = std::static_pointer_cast<ifx::MouseController>(
                        controller);
                auto camera = std::static_pointer_cast<ifx::CameraComponent>
                        (obj);

                auto current_scale = camera->getScale();
                camera->scale(current_scale
                              + (0.5f * mouse->GetScrollOffset().y));
            },
            ifx::MouseControllerEventType {
                    ifx::MouseControllerKeyType::MOUSE_SCROLL,
                    ifx::MouseControllerCallbackType::SCROLL_ACTIVE
            }
    );

    auto command_middle = command_factory.CreateMouseCommand(
            camera,
            [](std::shared_ptr<ifx::Controller> controller,
               std::shared_ptr<ifx::Controlable> obj){
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
                             movementSpeed *  0.1f);
                camera->move(yoffset * camera->GetUp() *
                             movementSpeed *  0.1f);

            },
            ifx::MouseControllerEventType {
                    ifx::MouseControllerKeyType::MOUSE_MIDDLE,
                    ifx::MouseControllerCallbackType::PRESSED
            }
    );

    controls->AddCommand(command_left);
    controls->AddCommand(command_right);
    controls->AddCommand(command_forward);
    controls->AddCommand(command_backwards);
    controls->AddCommand(command_down);
    controls->AddCommand(command_up);
    controls->AddCommand(command_rotate_mouse);
    controls->AddCommand(command_scroll);
    controls->AddCommand(command_middle);
}

}
