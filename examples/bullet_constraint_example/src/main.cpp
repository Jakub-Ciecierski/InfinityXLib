/**
 * Bullet example
 */

#include <game/game_loop.h>
#include <game/factory/game_loop_factory.h>
#include <graphics/factory/render_object_factory.h>
#include <graphics/rendering/renderer.h>
#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <game/game_object.h>
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
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <physics/simulations/bullet_physics_simulation.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h>
#include <BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h>
#include <BulletDynamics/ConstraintSolver/btConeTwistConstraint.h>
#include <graphics/factory/texture_factory.h>
#include <graphics/model/material.h>
#include <graphics/model/model.h>
#include <BulletDynamics/ConstraintSolver/btHingeConstraint.h>
#include <game/components/cameras/factory/camera_factory.h>
#include <graphics/factory/model_factory.h>
#include <game/components/render/render_component.h>
#include <graphics/factory/program_factory.h>
#include <game/components/lights/light_spotlight_component.h>
#include <game/components/lights/light_directional_component.h>
#include <game/components/physics/rigid_body_component.h>
#include <game/components/cameras/camera_component.h>

std::shared_ptr<ifx::LightDirectionalComponent> CreateDirectionalLight();
std::shared_ptr<ifx::LightSpotlightComponent> CreateSpotLight();
std::shared_ptr<ifx::RigidBodyComponent> CreateRigidBox(glm::vec3 scale);
std::shared_ptr<ifx::RigidBodyComponent> CreateRigidFloor();

std::shared_ptr<ifx::GameObject> CreateGameObjectCamera(
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::Game> game);
std::shared_ptr<ifx::GameObject> CreateGameObjectLight(
        std::shared_ptr<ifx::SceneContainer> scene);
std::shared_ptr<ifx::GameObject> CreateGameObjectBox(
        std::shared_ptr<ifx::SceneContainer> scene,
        const glm::vec3& scale, int tex_id = 0);
std::shared_ptr<ifx::GameObject> CreateGameObjectFloor(
        std::shared_ptr<ifx::SceneContainer> scene);
std::shared_ptr<ifx::GameObject> CreateGameObjectCeiling(
        std::shared_ptr<ifx::SceneContainer> scene);

void AddSpringConstraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);
void AddHeadTorsoConstraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);
void AddTorsoArm1Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);
void AddTorsoArm2Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);
void AddTorsoLeg1Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);
void AddTorsoLeg2Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);
void AddTorsoFeet1Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);
void AddTorsoFeet2Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2);

std::shared_ptr<ifx::RenderComponent> CreateFloor();

std::shared_ptr<ifx::RenderComponent> CreateFloor(){
    std::shared_ptr<Program> program = ifx::ProgramFactory().LoadMainProgram();
    std::shared_ptr<ifx::Model> model = ifx::ModelFactory::LoadFloorModel();

    auto render_object = std::shared_ptr<ifx::RenderComponent>(
            new ifx::RenderComponent(model));
    render_object->addProgram(program);

    float scaleFactor = 5.0f;
    render_object->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    render_object->rotateTo(glm::vec3(90, 0, 0));

    render_object->SetBeforeRender([](const Program* program){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    });
    render_object->SetAfterRender([](const Program* program){
        glDisable(GL_CULL_FACE);
    });

    return render_object;
}

std::shared_ptr<ifx::LightDirectionalComponent> CreateDirectionalLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    auto light_source = std::shared_ptr<ifx::LightDirectionalComponent>(
            new ifx::LightDirectionalComponent(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->rotateTo(glm::vec3(322, 295, 0));

    return light_source;
}

std::shared_ptr<ifx::LightSpotlightComponent> CreateSpotLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    auto light_source = std::shared_ptr<ifx::LightSpotlightComponent>(
            new ifx::LightSpotlightComponent(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));

    return light_source;
}

std::shared_ptr<ifx::RigidBodyComponent> CreateRigidBox(glm::vec3 scale){
    float a = 1;
    auto box_collision = std::shared_ptr<ifx::BoxCollisionShape>(
            new ifx::BoxCollisionShape(glm::vec3(a,a,a)));
    box_collision->collision_shape_bt()->setLocalScaling(btVector3(
            scale.x, scale.y, scale.z));

    auto mass = 1.0f;
    auto rigid_body = std::shared_ptr<ifx::RigidBodyComponent>(
            new ifx::RigidBodyComponent(box_collision, mass));

    return rigid_body;
}

std::shared_ptr<ifx::RigidBodyComponent> CreateRigidFloor(){
    auto box_collision = std::shared_ptr<ifx::BoxCollisionShape>(
            new ifx::BoxCollisionShape(glm::vec3(500,0.01,500)));

    auto mass = 0.0f;
    auto rigid_body = std::shared_ptr<ifx::RigidBodyComponent>(
            new ifx::RigidBodyComponent(box_collision, mass));

    return rigid_body;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectCamera(
        std::shared_ptr<ifx::SceneContainer> scene,
        std::shared_ptr<ifx::Game> game){
    auto game_object = scene->CreateAndAddEmptyGameObject();
    auto camera = ifx::CameraFactory().CreateCamera(
            game->game_loop()->renderer()->window());
    game_object->Add(std::dynamic_pointer_cast<ifx::GameComponent>(camera));

    return game_object;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectLight(
        std::shared_ptr<ifx::SceneContainer> scene){
    auto game_object = scene->CreateAndAddEmptyGameObject();

    std::shared_ptr<Program> program = ifx::ProgramFactory().loadLampProgram();
    std::shared_ptr<ifx::Model> model = ifx::ModelFactory::LoadLampModel();
    auto render_object = std::shared_ptr<ifx::RenderComponent>(
            new ifx::RenderComponent(model));
    render_object->addProgram(program);
    float scaleFactor = 0.05f;
    render_object->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    render_object->moveTo(glm::vec3(0, 0.3, 0));

    game_object->Add(std::dynamic_pointer_cast<ifx::GameComponent>(
            render_object));
    game_object->Add(CreateSpotLight());
    game_object->Add(CreateDirectionalLight());

    return game_object;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectBox(
        std::shared_ptr<ifx::SceneContainer> scene,
        const glm::vec3& scale, int tex_id){
    float scale_factor = 0.25;
    glm::vec3 scaled_scale = scale * scale_factor;
    auto game_object = scene->CreateAndAddEmptyGameObject();

    std::shared_ptr<ifx::Model> model = ifx::ModelFactory::LoadCubeModel();
    std::shared_ptr<Program> program = ifx::ProgramFactory().LoadMainProgram();
    auto render_object = std::shared_ptr<ifx::RenderComponent>(
            new ifx::RenderComponent(model));
    render_object->addProgram(program);
    render_object->scale(scaled_scale);

    game_object->Add(CreateRigidBox(scaled_scale));
    game_object->Add(render_object);

    std::string str_text_diff = "";
    std::string str_text_spec = "";

    if(tex_id == 1){
        str_text_diff = "portal/portal_wall.jpg";
        str_text_spec = "portal/portal_wall_spec.jpg";
    }else if(tex_id == 0){
        str_text_diff = "robot/head.jpg";
        str_text_spec = "robot/head_spec.jpg";
    }

    auto texture_diff = ifx::Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath(str_text_diff,
                                     ifx::ResourceType::TEXTURE),
            ifx::TextureTypes::DIFFUSE);
    auto texture_spec = ifx::Texture2D::MakeTexture2DFromFile(
            ifx::Resources::GetInstance()
                    .GetResourcePath(str_text_spec,
                                     ifx::ResourceType::TEXTURE),
            ifx::TextureTypes::SPECULAR);

    auto material = std::make_shared<ifx::Material>();
    material->AddTexture(texture_diff);
    material->AddTexture(texture_spec);
    render_object->models()[0]->getMesh(0)->material(material);

    return game_object;

}
std::shared_ptr<ifx::GameObject> CreateGameObjectFloor(
        std::shared_ptr<ifx::SceneContainer> scene){
    auto game_object = scene->CreateAndAddEmptyGameObject();

    game_object->Add(CreateFloor());
    game_object->Add(CreateRigidFloor());
    return game_object;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectCeiling(
        std::shared_ptr<ifx::SceneContainer> scene){
    auto game_object = scene->CreateAndAddEmptyGameObject();

    game_object->Add(CreateFloor());
    game_object->Add(CreateRigidFloor());
    game_object->rotateTo(glm::vec3(0,0,180));
    return game_object;
}

void AddSpringConstraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    btTransform frameInA, frameInB;
    frameInA = btTransform::getIdentity();
    frameInA.setOrigin(btVector3(btScalar(0.), btScalar(2.), btScalar(0.)));
    frameInB = btTransform::getIdentity();
    frameInB.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(0.)));

    btGeneric6DofSpringConstraint* constraint
            = new btGeneric6DofSpringConstraint(*body1->rigid_body_bt(),
                                                *body2->rigid_body_bt(),
                                                frameInA,
                                                frameInB, true);
    constraint->setLimit(1, 1, -1); // free
    constraint->enableSpring(1, true);
    constraint->setStiffness(1, 100);
    constraint->setDamping(1, 0.05);
    constraint->setEquilibriumPoint(1, 0);

    simulation->dynamics_world_bt()->addConstraint(constraint, true);
}

void AddHeadTorsoConstraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    btVector3 pivot1(0, -1.3, 0);
    btVector3 pivot2(0, 0.9, 0);

    auto constraint = new btPoint2PointConstraint(
            *body1->rigid_body_bt(),
            *body2->rigid_body_bt(), pivot1, pivot2);
    simulation->dynamics_world_bt()->addConstraint(constraint, true);
}

void AddTorsoArm1Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    //btVector3 pivot1(0, 0, -1.0);
    btVector3 pivot1(0, 0.5, -0.6);
    btVector3 pivot2(0, -1.0, 0.0);

    auto constraint = new btPoint2PointConstraint(
            *body1->rigid_body_bt(),
            *body2->rigid_body_bt(), pivot1, pivot2);
    simulation->dynamics_world_bt()->addConstraint(constraint, true);
}

void AddTorsoArm2Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    btVector3 pivot1(0, 0.5, 0.6);
    btVector3 pivot2(0, -1.0, 0.0);

    auto constraint = new btPoint2PointConstraint(
            *body1->rigid_body_bt(),
            *body2->rigid_body_bt(), pivot1, pivot2);
    simulation->dynamics_world_bt()->addConstraint(constraint, true);
}

void AddTorsoLeg1Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    btVector3 pivot1(0, -1.3, -0.5);
    btVector3 pivot2(0, 1, 0.0);

    auto constraint = new btPoint2PointConstraint(
            *body1->rigid_body_bt(),
            *body2->rigid_body_bt(), pivot1, pivot2);
    simulation->dynamics_world_bt()->addConstraint(constraint, true);
}

void AddTorsoLeg2Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    btVector3 pivot1(0, -1.3, 0.5);
    btVector3 pivot2(0, 1, 0.0);

    auto constraint = new btPoint2PointConstraint(
            *body1->rigid_body_bt(),
            *body2->rigid_body_bt(), pivot1, pivot2);
    simulation->dynamics_world_bt()->addConstraint(constraint, true);
}

void AddTorsoFeet1Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    btVector3 pivotInA(0, -1 ,0);
    btVector3 pivotInB(0.4, 0, 0);
    btVector3 axisInA(0,0,1);
    btVector3 axisInB(0,0,1);

    btHingeConstraint* hinge
            = new btHingeAccumulatedAngleConstraint(*body1->rigid_body_bt(),
                                    *body2->rigid_body_bt(),
                                    pivotInA,pivotInB,
                                    axisInA,axisInB, true);
    hinge->setLimit(1.5*M_PI, 2*M_PI, 10);
    simulation->dynamics_world_bt()->addConstraint(hinge, true);
}

void AddTorsoFeet2Constraint(
        std::shared_ptr<ifx::BulletPhysicsSimulation> simulation,
        std::shared_ptr<ifx::RigidBodyComponent> body1,
        std::shared_ptr<ifx::RigidBodyComponent> body2){
    btVector3 pivotInA(0, -1 ,0);
    btVector3 pivotInB(0.4, 0, 0);
    btVector3 axisInA(0,0,1);
    btVector3 axisInB(0,0,1);

    btHingeConstraint* hinge
            = new btHingeAccumulatedAngleConstraint(*body1->rigid_body_bt(),
                                                    *body2->rigid_body_bt(),
                                                    pivotInA,pivotInB,
                                                    axisInA,axisInB, true);
    hinge->setLimit(1.5*M_PI, 2*M_PI, 10);
    simulation->dynamics_world_bt()->addConstraint(hinge, true);
}

int main() {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto lights = CreateGameObjectLight(game->scene());
    lights->moveTo(glm::vec3(0.0f, 3.0f, 0.0f));
    lights->rotateTo(glm::vec3(0,180,0));

    auto camera = CreateGameObjectCamera(game->scene(), game);
    camera->moveTo(glm::vec3(-7, 2, 0));

    auto floor = CreateGameObjectFloor(game->scene());
    floor->moveTo(glm::vec3(0.0f, 0.0f, 0.0f));

    auto ceiling = CreateGameObjectCeiling(game->scene());
    ceiling->moveTo(glm::vec3(0.0f, 10.0f, 0.0f));

    glm::vec3 scale1 = glm::vec3(3,3,3);
    auto head = CreateGameObjectBox(game->scene(), scale1, 0);
    head->moveTo(glm::vec3(0.0f, 7.0f, 0.0f));

    glm::vec3 scale2 = glm::vec3(2,5,2);
    auto torso = CreateGameObjectBox(game->scene(), scale2, 1);
    torso->moveTo(glm::vec3(0.0f, 4.0f, 0.0f));

    glm::vec3 scale3 = glm::vec3(0.7,4,0.7);
    auto arm1 = CreateGameObjectBox(game->scene(), scale3, 1);
    arm1->moveTo(glm::vec3(0.0f, 3.6f, -1.4f));
    arm1->rotateTo(glm::vec3(218.0f, 0.0f, 0.0f));

    auto arm2 = CreateGameObjectBox(game->scene(), scale3, 1);
    arm2->moveTo(glm::vec3(0.0f, 3.6f, 1.4f));
    arm2->rotateTo(glm::vec3(140.0f, 0.0f, 0.0f));

    auto leg1 = CreateGameObjectBox(game->scene(), scale3, 1);
    leg1->moveTo(glm::vec3(-0.32f, 1.7f, -0.32f));

    auto leg2 = CreateGameObjectBox(game->scene(), scale3, 1);
    leg2->moveTo(glm::vec3(-0.32f, 1.7f, 0.32f));

    glm::vec3 scale4 = glm::vec3(1.56, 0.25, 1.03);
    auto feet1 = CreateGameObjectBox(game->scene(), scale4, 1);
    feet1->moveTo(glm::vec3(-0.76f, 0.6f, -0.32f));
    //feet1->rotateTo(glm::vec3(180.0f, 0.0f, 0.0f));

    auto feet2 = CreateGameObjectBox(game->scene(), scale4, 1);
    feet2->moveTo(glm::vec3(-0.76f, 0.6f, 0.32f));

    auto ceiling_rigid_bodies = ceiling->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto ceiling_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            ceiling_rigid_bodies[0]);

    auto head_rigid_bodies = head->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto head_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            head_rigid_bodies[0]);

    auto torso_rigid_bodies = torso->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto torso_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            torso_rigid_bodies[0]);

    auto arm1_rigid_bodies = arm1->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto arm1_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            arm1_rigid_bodies[0]);

    auto arm2_rigid_bodies = arm2->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto arm2_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            arm2_rigid_bodies[0]);

    auto leg1_rigid_bodies = leg1->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto leg1_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            leg1_rigid_bodies[0]);

    auto leg2_rigid_bodies = leg2->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto leg2_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            leg2_rigid_bodies[0]);

    auto feet1_rigid_bodies = feet1->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto feet1_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            feet1_rigid_bodies [0]);

    auto feet2_rigid_bodies = feet2->GetComponents(
            std::move(ifx::GameComponentType::PHYSICS));
    auto feet2_rigid_body = std::static_pointer_cast<ifx::RigidBodyComponent>(
            feet2_rigid_bodies [0]);

    AddSpringConstraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                           (game->game_loop()->physics_simulation()),
            ceiling_rigid_body, head_rigid_body);

    AddHeadTorsoConstraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                    (game->game_loop()->physics_simulation()),
            head_rigid_body, torso_rigid_body);

    AddTorsoArm1Constraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                    (game->game_loop()->physics_simulation()),
            torso_rigid_body, arm1_rigid_body);

    AddTorsoArm2Constraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                    (game->game_loop()->physics_simulation()),
            torso_rigid_body, arm2_rigid_body);

    AddTorsoLeg1Constraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                    (game->game_loop()->physics_simulation()),
            torso_rigid_body, leg1_rigid_body);

    AddTorsoLeg2Constraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                    (game->game_loop()->physics_simulation()),
            torso_rigid_body, leg2_rigid_body);

    AddTorsoFeet1Constraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                    (game->game_loop()->physics_simulation()),
            leg1_rigid_body, feet1_rigid_body);

    AddTorsoFeet2Constraint(
            std::static_pointer_cast<ifx::BulletPhysicsSimulation>
                    (game->game_loop()->physics_simulation()),
            leg2_rigid_body, feet2_rigid_body);

    auto gui = std::shared_ptr<ExampleGUI>(
            new ExampleGUI(
                    game->game_loop()->renderer()->window()->getHandle(),
                    game->scene(),
                    game->game_loop()->physics_simulation()));
    game->game_loop()->renderer()->SetGUI(gui);

    game->Start();
}
