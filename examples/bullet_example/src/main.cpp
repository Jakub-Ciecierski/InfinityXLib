#include <game/game_loop.h>
#include <game/factory/game_loop_factory.h>
#include <graphics/factory/render_object_factory.h>
#include <graphics/rendering/renderer.h>
#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <object/game_object.h>
#include <graphics/factory/scene_factory.h>
#include <graphics/lighting/light_source.h>
#include <graphics/lighting/types/light_directional.h>
#include <graphics/lighting/types/light_spotlight.h>

#include <graphics/rendering/camera/camera.h>
#include <engine_gui/factory/engine_gui_factory.h>
#include <graphics/rendering/renderer.h>
#include <engine_gui/engine_gui.h>
#include <example_gui.h>
#include <physics/rigid_body.h>
#include <physics/collision/shapes/box_collision_shape.h>
#include "physics/collision/shapes/static_plane_shape.h"

#include <LinearMath/btTransform.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight();
std::shared_ptr<ifx::LightSpotlight> CreateSpotLight();
std::shared_ptr<ifx::RigidBody> CreateRigidBox();
std::shared_ptr<ifx::RigidBody> CreateRigidFloor();

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    auto light_source = std::shared_ptr<ifx::LightDirectional>(
            new ifx::LightDirectional(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));

    return light_source;
}

std::shared_ptr<ifx::LightSpotlight> CreateSpotLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    auto light_source = std::shared_ptr<ifx::LightSpotlight>(
            new ifx::LightSpotlight(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));

    return light_source;
}

std::shared_ptr<ifx::RigidBody> CreateRigidBox(){
    float a = 1;
    float scale = 1;
    auto box_collision = std::shared_ptr<ifx::BoxCollisionShape>(
            new ifx::BoxCollisionShape(glm::vec3(a,a,a)));
    box_collision->collision_shape_bt()->setLocalScaling(btVector3(
            scale, scale, scale));

    auto mass = 1.0f;
    auto rigid_body = std::shared_ptr<ifx::RigidBody>(
            new ifx::RigidBody(box_collision, mass));

    return rigid_body;
}

std::shared_ptr<ifx::RigidBody> CreateRigidFloor(){
    auto collion_shape = std::shared_ptr<ifx::StaticPlaneShape>(
            new ifx::StaticPlaneShape(glm::vec3(0,1,0),1));
    auto box_collision = std::shared_ptr<ifx::BoxCollisionShape>(
            new ifx::BoxCollisionShape(glm::vec3(500,0.01,500)));

    auto mass = 0.0f;
    auto rigid_body = std::shared_ptr<ifx::RigidBody>(
            new ifx::RigidBody(box_collision, mass));

    return rigid_body;
}

int main() {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_object1 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto game_object2 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto game_object3 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto game_object4 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto game_object5 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());

    auto lamp = ifx::RenderObjectFactory().CreateLampObject();

    game_object2->Add(std::move(lamp));
    game_object2->Add(CreateSpotLight());
    game_object2->Add(CreateDirectionalLight());
    game_object2->moveTo(glm::vec3(0.0f, 4.0f, 0.0f));

    game_object3->Add(
            ifx::SceneFactory().CreateCamera(game->game_loop()->renderer()->window()));

    game_object4->Add(CreateRigidBox());
    game_object4->Add(ifx::RenderObjectFactory().CreateCube());
    game_object4->moveTo(glm::vec3(0.0f, 10.0f, 0.0f));

    game_object5->Add(CreateRigidBox());
    game_object5->Add(ifx::RenderObjectFactory().CreateCube());
    game_object5->moveTo(glm::vec3(0.0f, 15.0f, 0.0f));

    game_object1->Add(ifx::RenderObjectFactory().CreateFloor());
    game_object1->Add(CreateRigidFloor());
    game_object1->moveTo(glm::vec3(0.0f, 0.0f, 0.0f));


    game->scene()->Add(game_object1);
    game->scene()->Add(game_object2);
    game->scene()->Add(game_object3);
    game->scene()->Add(game_object4);
    game->scene()->Add(game_object5);

    auto gui = std::shared_ptr<ExampleGUI>(
            new ExampleGUI(
                    game->game_loop()->renderer()->window()->getHandle(),
                    game->scene()));
    game->game_loop()->renderer()->SetGUI(gui);

    game->Start();
}
