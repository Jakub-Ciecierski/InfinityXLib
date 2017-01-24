#include "graphics/rendering/scene_renderer.h"

#include <graphics/lighting/light_group.h>
#include <graphics/rendering/camera/camera.h>
#include <object/render_object.h>

namespace ifx {

SceneRenderer::SceneRenderer(){
    light_group_ = std::shared_ptr<LightGroup>(new LightGroup());
}
SceneRenderer::~SceneRenderer(){}

void SceneRenderer::Render(int id) const{
    for(auto& render_object : render_objects_){
        if(id == 0 && render_object->id().key_id() == -2)
            continue;
        if(id == 1 && render_object->id().key_id() == -1)
            continue;
        Render(render_object);
    }
}

void SceneRenderer::Render() const{
    for(auto& render_object : render_objects_){
        Render(render_object);
    }
}

void SceneRenderer::Render(const std::shared_ptr<Program> program) const{
    camera_->use(*(program));
    light_group_->use(*(program));
    for(unsigned int i = 0; i < render_objects_.size(); i++)
        render_objects_[i]->Render(*(program));
}

void SceneRenderer::Render(std::shared_ptr<RenderObject> render_object) const{
    const std::vector<std::shared_ptr<Program>>& programs
            = render_object->programs();
    for(unsigned int j = 0; j < programs.size(); j++){
        camera_->use(*(programs[j]));
        light_group_->use(*(programs[j]));
        render_object->Render(*(programs[j]));
    }
}

void SceneRenderer::Add(std::shared_ptr<RenderObject> render_object){
    render_objects_.push_back(render_object);
}

void SceneRenderer::Add(std::shared_ptr<LightSource> light_source){
    light_group_->Add(light_source);
}

void SceneRenderer::Add(std::shared_ptr<Camera> camera){
    camera_ = camera;
}

bool SceneRenderer::Remove(std::shared_ptr<RenderObject> render_object){
    for(unsigned int i = 0; i < render_objects_.size(); i++){
        if(render_objects_[i] == render_object){
            render_objects_.erase(render_objects_.begin() + i);
            return true;
        }
    }
    return false;
}
bool SceneRenderer::Remove(std::shared_ptr<LightSource> light_source){
    return light_group_->Remove(light_source);
}
bool SceneRenderer::Remove(std::shared_ptr<Camera> camera){
    return false;
}

}