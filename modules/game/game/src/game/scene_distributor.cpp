#include "game/scene_distributor.h"

#include <graphics/rendering/scene_renderer.h>
#include <physics/physics_simulation.h>
#include <game/game_object.h>
#include <game/game_component.h>

#include <graphics/rendering/render_object.h>
#include <physics/rigid_body.h>
#include <graphics/lighting/light_source.h>
#include <graphics/rendering/camera/camera.h>
#include <game/components/render/render_component.h>
#include <game/components/cameras/camera_component.h>
#include <game/components/physics/rigid_body_component.h>

namespace ifx {

SceneDistributor::SceneDistributor(
    std::shared_ptr<SceneRenderer> scene_renderer,
    std::shared_ptr<PhysicsSimulation> physics_simulation)
    : scene_renderer_(scene_renderer),
      physics_simulation_(physics_simulation) {}

SceneDistributor::~SceneDistributor() {}

void SceneDistributor::Add(std::shared_ptr<GameObject> game_object) {
    auto components = game_object->GetComponents();
    for (auto &component : components) {
        Add(component);
    }
}

bool SceneDistributor::Remove(std::shared_ptr<GameObject> game_object) {
    auto components = game_object->GetComponents();
    for (auto &component : components) {
        Remove(component);
    }
    return true;
}

void SceneDistributor::Add(std::shared_ptr<GameComponent> game_component) {
    switch (game_component->type()) {
        case GameComponentType::RENDER:
            Add(std::dynamic_pointer_cast<RenderComponent>(game_component));
            break;
        case GameComponentType::LIGHT:
            Add(std::dynamic_pointer_cast<LightSource>(game_component));
            break;
        case GameComponentType::CAMERA:
            Add(std::dynamic_pointer_cast<CameraComponent>(game_component));
            break;
        case GameComponentType::PHYSICS:
            Add(std::dynamic_pointer_cast<RigidBodyComponent>(game_component));
            break;
    }
}

bool SceneDistributor::Remove(std::shared_ptr<GameComponent> game_component) {
    switch (game_component->type()) {
        case GameComponentType::RENDER:
            Remove(std::dynamic_pointer_cast<RenderComponent>(game_component));
            break;
        case GameComponentType::LIGHT:
            Remove(std::dynamic_pointer_cast<LightSource>(game_component));
            break;
        case GameComponentType::CAMERA:
            Remove(std::dynamic_pointer_cast<CameraComponent>(game_component));
            break;
        case GameComponentType::PHYSICS:
            Remove(std::dynamic_pointer_cast<RigidBodyComponent>
                       (game_component));
            break;
    }
    return false;
}

void SceneDistributor::Add(std::shared_ptr<RenderComponent> render_object) {
    scene_renderer_->Add(render_object);
}

void SceneDistributor::Add(std::shared_ptr<LightSource> light_source) {
    scene_renderer_->Add(light_source);
}

void SceneDistributor::Add(std::shared_ptr<CameraComponent> camera) {
    scene_renderer_->Add(camera);
}

void SceneDistributor::Add(std::shared_ptr<RigidBodyComponent> rigid_body) {
    physics_simulation_->Add(rigid_body);
}

bool SceneDistributor::Remove(std::shared_ptr<RenderComponent> render_object) {
    return scene_renderer_->Remove(render_object);
}

bool SceneDistributor::Remove(std::shared_ptr<LightSource> light_source) {
    return scene_renderer_->Remove(light_source);
}

bool SceneDistributor::Remove(std::shared_ptr<CameraComponent> camera) {
    return scene_renderer_->Remove(camera);
}

bool SceneDistributor::Remove(std::shared_ptr<RigidBodyComponent> rigid_body) {
    return physics_simulation_->Remove(rigid_body);
}

}