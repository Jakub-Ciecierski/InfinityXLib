#include <editor/factory/editor_factory.h>
#include <editor/editor.h>

#include <gui/gui.h>

#include <physics/rigid_body.h>
#include <physics/collision/shapes/box_collision_shape.h>
#include "physics/collision/shapes/static_plane_shape.h"
#include <physics/simulations/bullet_physics_simulation.h>

#include <factory/texture_factory.h>
#include <factory/model_factory.h>
#include <factory/program_factory.h>
#include <factory/render_object_factory.h>

#include <game/components/cameras/factory/camera_factory.h>
#include <game/components/render/render_component.h>
#include <game/components/lights/light_spotlight_component.h>
#include <game/components/lights/light_directional_component.h>
#include <game/components/lights/light_point_component.h>
#include <game/components/physics/rigid_body_component.h>
#include <game/components/cameras/camera_component.h>
#include <game/components/lights/factory/light_component_factory.h>
#include <game/resources/resource_context.h>
#include <game/game_loop.h>
#include <game/factory/game_loop_factory.h>
#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <game/game_object.h>

#include <graphics/model/material.h>
#include <graphics/model/model.h>
#include <graphics/shaders/textures/texture_creator.h>
#include <graphics/rendering/renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/rendering/rendering_effect.h>
#include <graphics/factory/scene_factory.h>

#include <resources/resource_manager.h>
#include <resources/resources.h>

#include <controls/controls.h>
#include <controls/command/factory/command_factory.h>
#include <controls/command/commands/keyboard_command.h>
#include <controls/command/commands/mouse_command.h>
#include <controls/controller/controllers/mouse_controller.h>

#include <GL/glew.h>
#include <physics/factory/physx_physics_simulation_factory.h>

void SetKeybinds(
        std::shared_ptr<ifx::Controls> controls,
        std::shared_ptr<ifx::CameraComponent> camera);

std::shared_ptr<ifx::RigidBodyComponent> CreateRigidBox(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        glm::vec3 scale);
std::shared_ptr<ifx::RigidBodyComponent> CreateRigidFloor(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation);

std::shared_ptr<ifx::GameObject> CreateGameObjectCamera(
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::Game> game);
std::shared_ptr<ifx::GameObject> CreateGameObjectLight(
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::TextureCreator> texture_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::ProgramCreator> program_creato);

std::shared_ptr<ifx::GameObject> CreateGameObjectBox(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::TextureCreator> texture_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        const glm::vec3& scale, int tex_id = 0);

std::shared_ptr<ifx::GameObject> CreateGameObjectFloor(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::TextureCreator> texture_creator);
std::shared_ptr<ifx::GameObject> CreateGameObjectCeiling(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::TextureCreator> texture_creator);

std::shared_ptr<ifx::RenderComponent> CreateFloor(
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::TextureCreator> texture_creator);

void SetKeybinds(
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

                camera->moveForward(0.5f * mouse->GetScrollOffset().y);
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

std::shared_ptr<ifx::RenderComponent> CreateFloor(
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::TextureCreator> texture_creator){
    std::shared_ptr<ifx::Program> program
            = ifx::ProgramFactory(program_creator).LoadMainProgram();
    std::shared_ptr<ifx::Model> model = ifx::ModelFactory(
            model_creator, texture_creator).LoadFloorModel();

    auto render_object = std::shared_ptr<ifx::RenderComponent>(
            new ifx::RenderComponent(model));
    render_object->addProgram(program);

    float scaleFactor = 5.0f;
    render_object->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    render_object->rotateTo(glm::vec3(90, 0, 0));

    render_object->SetBeforeRender([](const ifx::Program* program){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    });
    render_object->SetAfterRender([](const ifx::Program* program){
        glDisable(GL_CULL_FACE);
    });

    return render_object;
}

std::shared_ptr<ifx::RigidBodyComponent> CreateRigidBox(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        glm::vec3 scale){
    float a = 1;
    auto box_collision = std::shared_ptr<ifx::BoxCollisionShape>(
            new ifx::BoxCollisionShape(glm::vec3(a,a,a)));

    auto mass = 1.0f;
    auto rigid_body = std::shared_ptr<ifx::RigidBodyComponent>(
            new ifx::RigidBodyComponent(
                    physics_simulation,
                    ifx::RigidBodyParams{box_collision, mass}));

    return rigid_body;
}

std::shared_ptr<ifx::RigidBodyComponent> CreateRigidFloor(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation){
    auto box_collision = std::shared_ptr<ifx::StaticPlaneShape>(
            new ifx::StaticPlaneShape(glm::vec3(0,1,0), 0));

    auto mass = 0.0f;
    auto rigid_body = std::shared_ptr<ifx::RigidBodyComponent>(
            new ifx::RigidBodyComponent(
                    physics_simulation,
                    ifx::RigidBodyParams{box_collision, mass}));

    return rigid_body;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectCamera(
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::Game> game){
    auto game_object = scene->CreateAndAddEmptyGameObject();
    auto camera = ifx::CameraFactory().CreateCamera(
            game->game_loop()->renderer()->window().get());

    SetKeybinds(game->game_loop()->controls(), camera);

    game_object->Add(std::dynamic_pointer_cast<ifx::GameComponent>(camera));

    return game_object;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectLight(
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::TextureCreator> texture_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::ProgramCreator> program_creator){
    auto game_object = scene->CreateAndAddEmptyGameObject();

    std::shared_ptr<ifx::Program> program
            = ifx::ProgramFactory(program_creator).loadLampProgram();
    std::shared_ptr<ifx::Model> model = ifx::ModelFactory(
            model_creator, texture_creator).LoadLampModel();
    auto render_object = std::shared_ptr<ifx::RenderComponent>(
            new ifx::RenderComponent(model));
    render_object->addProgram(program);
    float scaleFactor = 0.05f;
    render_object->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    render_object->moveTo(glm::vec3(0, 0.3, 0));

    game_object->Add(render_object);
    game_object->Add(ifx::LightComponentFactory().CreateDirectionalLight(
            texture_creator, program_creator));
    game_object->Add(ifx::LightComponentFactory().CreateSpotLight(
            texture_creator, program_creator));
    /*
    game_object->Add(
            std::dynamic_pointer_cast<ifx::GameComponent>
                    (ifx::LightComponentFactory()
            .CreatePointLight()));
*/
    ifx::LightParams light;
    auto light_source = std::shared_ptr<ifx::LightPointComponent>(
            new ifx::LightPointComponent(light));
    /*
    game_object->Add(std::static_pointer_cast<ifx::GameComponent>
                             (light_source));*/

    return game_object;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectBox(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::TextureCreator> texture_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        const glm::vec3& scale, int tex_id){
    float scale_factor = 0.25;
    glm::vec3 scaled_scale = scale * scale_factor;
    auto game_object = scene->CreateAndAddEmptyGameObject();

    std::shared_ptr<ifx::Model> model = ifx::ModelFactory(
            model_creator, texture_creator).LoadCubeModel();
    std::shared_ptr<ifx::Program> program
            = ifx::ProgramFactory(program_creator).LoadMainProgram();
    auto render_object = std::shared_ptr<ifx::RenderComponent>(
            new ifx::RenderComponent(model));
    render_object->addProgram(program);

    game_object->Add(CreateRigidBox(physics_simulation, scaled_scale));
    game_object->Add(render_object);
    game_object->scale(scale_factor);

    return game_object;

}
std::shared_ptr<ifx::GameObject> CreateGameObjectFloor(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::TextureCreator> texture_creator){
    auto game_object = scene->CreateAndAddEmptyGameObject();

    game_object->Add(CreateFloor(program_creator,
                                 model_creator,
                                 texture_creator));
    game_object->Add(CreateRigidFloor(physics_simulation));
    return game_object;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectCeiling(
        std::shared_ptr<ifx::PhysicsSimulation> physics_simulation,
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::ProgramCreator> program_creator,
        std::shared_ptr<ifx::ModelCreator> model_creator,
        std::shared_ptr<ifx::TextureCreator> texture_creator){
    auto game_object = scene->CreateAndAddEmptyGameObject();

    game_object->Add(CreateFloor(program_creator,
                                 model_creator,
                                 texture_creator));
    game_object->Add(CreateRigidFloor(physics_simulation));
    game_object->rotateTo(glm::vec3(0,0,180));
    return game_object;
}


int main() {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());

    auto game = game_factory->Create();

    auto lights = CreateGameObjectLight(
            game->scene(),
            game->resource_creator()->texture_creator(),
            game->resource_creator()->model_creator(),
            game->resource_creator()->program_creator());

    lights->moveTo(glm::vec3(0.0f, 3.0f, 0.0f));
    lights->rotateTo(glm::vec3(0,180,0));

    auto camera = CreateGameObjectCamera(game->scene(), game);
    camera->moveTo(glm::vec3(-7, 2, 0));

    auto floor = CreateGameObjectFloor(
            game->game_loop()->physics_simulation(),
            game->scene(),
            game->resource_creator()->program_creator(),
            game->resource_creator()->model_creator(),
            game->resource_creator()->texture_creator());
    floor->moveTo(glm::vec3(0.0f, 0.0f, 0.0f));

    auto ceiling = CreateGameObjectCeiling(
            game->game_loop()->physics_simulation(),
            game->scene(),
            game->resource_creator()->program_creator(),
            game->resource_creator()->model_creator(),
            game->resource_creator()->texture_creator());
    ceiling->moveTo(glm::vec3(0.0f, 10.0f, 0.0f));

    glm::vec3 scale1 = glm::vec3(3,3,3);
    auto head = CreateGameObjectBox(
            game->game_loop()->physics_simulation(),
            game->scene(),
            game->resource_creator()->texture_creator(),
            game->resource_creator()->model_creator(),
            game->resource_creator()->program_creator(),
            scale1, 0);
    head->moveTo(glm::vec3(0.0f, 7.0f, 0.0f));

    auto editor = ifx::EditorFactory().CreateEngineGUI(
            game->game_loop()->renderer()->window(),
            game->scene(),
            game->game_loop()->physics_simulation(),
            game->resource_creator());
    game->game_loop()->gui()->AddGUIPart(editor);

    auto scene_renderer = game->game_loop()->renderer()->scene_renderer();
    for(auto& rendering_effect : scene_renderer->rendering_effects()){
        if(rendering_effect->name() == "main.prog"){
            for(auto& render_object : scene_renderer->render_objects()){
                rendering_effect->RegisterRenderObject(render_object);
            }
        }
    }

    game->Start();
}



