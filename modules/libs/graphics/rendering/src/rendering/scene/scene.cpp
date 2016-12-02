#include "scene/scene.h"

#include <controls/controls.h>

namespace ifx {

Scene::Scene(std::unique_ptr<LightGroup> light_group,
             std::unique_ptr<Camera> camera) :
        light_group_(std::move(light_group)),
        camera_(std::move(camera)) {}

Scene::Scene(std::vector<std::unique_ptr<RenderObject>> render_objects,
             std::unique_ptr<LightGroup> light_group,
             std::unique_ptr<Camera> camera) :
        light_group_(std::move(light_group)),
        camera_(std::move(camera)) {
    for(unsigned int i = 0; i < render_objects.size(); i++){
        render_objects_.push_back(std::move(render_objects[i]));
    }
}

Scene::~Scene(){}

void Scene::AddRenderObject(std::shared_ptr<RenderObject> render_object){
    render_objects_.push_back(render_object);
}

bool Scene::DeleteRenderObject(RenderObject* render_object){
    for(int i = 0;i < render_objects_.size(); i++){
        if(render_object == render_objects_[i].get()){
            render_objects_[i].reset();
            render_objects_.erase(render_objects_.begin() + i);
            return true;
        }
    }
    return false;
}

void Scene::ReloadProgams(){
    for(auto& render_object : render_objects_){
        const std::vector<std::shared_ptr<Program>>& programs =
                render_object->programs();
        for(auto& program : programs)
            program->Reload();
    }
}

void Scene::SetCamera(std::unique_ptr<Camera> camera){
    camera_ = std::move(camera);
}

void Scene::render(int id){
    for(auto& render_object : render_objects_){
        if(id == 0 && render_object->id().key() == -2)
            continue;
        if(id == 1 && render_object->id().key() == -1)
            continue;
        render(render_object.get());
    }

}

void Scene::render(const Program* program){
    camera_->use(*program);
    light_group_->use(*program);
    for(unsigned int i = 0; i < render_objects_.size(); i++)
        render_objects_[i]->render(*program);
}

void Scene::render(RenderObject* render_object){
    const std::vector<std::shared_ptr<Program>>& programs
            = render_object->programs();
    for(unsigned int j = 0; j < programs.size(); j++){
        camera_->use(*(programs[j].get()));
        light_group_->use(*(programs[j].get()));
        render_object->render(*(programs[j].get()));
    }
}

void Scene::update(){
    updateObjects();
    camera_->update();
}

void Scene::updateObjects(){
    for(auto& render_object : render_objects_)
        render_object->update();
}

}