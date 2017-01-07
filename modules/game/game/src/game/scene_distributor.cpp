#include "game/scene_distributor.h"

#include <graphics/rendering/scene_renderer.h>
#include <physics/physics_simulation.h>
#include <object/game_object.h>
#include <object/game_component.h>

#include <object/render_object.h>
#include <physics/rigid_body.h>
#include <graphics/lighting/light_source.h>
#include <graphics/rendering/camera/camera.h>

namespace ifx {

SceneDistributor::SceneDistributor(
        std::shared_ptr<SceneRenderer> scene_renderer,
        std::shared_ptr<PhysicsSimulation> physics_simulation)
        : scene_renderer_(scene_renderer),
          physics_simulation_(physics_simulation){}

SceneDistributor::~SceneDistributor(){}

void SceneDistributor::Add(std::shared_ptr<GameObject> game_object){
    auto components = game_object->GetComponents();
    for(auto& component : components){
        switch(component->type()){
            case GameComponentType::RENDER:
                Add(std::static_pointer_cast<RenderObject>(component));
                break;
            case GameComponentType::LIGHT:
                Add(std::static_pointer_cast<LightSource>(component));
                break;
            case GameComponentType::CAMERA:
                Add(std::static_pointer_cast<Camera>(component));
                break;
            case GameComponentType::PHYSICS:
                Add(std::static_pointer_cast<RigidBody>(component));
                break;
        }
    }
}

bool SceneDistributor::Remove(std::shared_ptr<GameObject> game_object){
    auto components = game_object->GetComponents();
    for(auto& component : components){
        switch(component->type()){
            case GameComponentType::RENDER:
                return Remove(std::static_pointer_cast<RenderObject>
                                      (component));
            case GameComponentType::LIGHT:
                return Remove(std::static_pointer_cast<LightSource>(component));
            case GameComponentType::CAMERA:
                return Remove(std::static_pointer_cast<Camera>(component));
            case GameComponentType::PHYSICS:
                return Remove(std::static_pointer_cast<RigidBody>(component));
        }
    }
}

void SceneDistributor::Add(std::shared_ptr<RenderObject> render_object){
    scene_renderer_->Add(render_object);
}

void SceneDistributor::Add(std::shared_ptr<LightSource> light_source){
    scene_renderer_->Add(light_source);
}

void SceneDistributor::Add(std::shared_ptr<Camera> camera){
    scene_renderer_->Add(camera);
}

void SceneDistributor::Add(std::shared_ptr<RigidBody> rigid_body){

}

bool SceneDistributor::Remove(std::shared_ptr<RenderObject> render_object){
    return scene_renderer_->Remove(render_object);
}

bool SceneDistributor::Remove(std::shared_ptr<LightSource> light_source){
    return scene_renderer_->Remove(light_source);
}

bool SceneDistributor::Remove(std::shared_ptr<Camera> camera){
    return scene_renderer_->Remove(camera);
}

bool SceneDistributor::Remove(std::shared_ptr<RigidBody> rigid_body){

}

}