#include "graphics/lighting/light_group.h"

using namespace ifx;

LightGroup::LightGroup() :
        point_light_count_(0),
        spotlight_light_count_(0),
        directional_light_count_(0){}

LightGroup::~LightGroup(){}

void LightGroup::bindLightCount(const Program &program) {
    program.use();

    GLint pointLightCountLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_POINTLIGHT_COUNT.c_str());
    GLint dirLightCountLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_DIRLIGHT_COUNT.c_str());
    GLint spotLightCountLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_SPOTLIGHT_COUNT.c_str());

    glUniform1i(pointLightCountLoc, point_light_count_);
    glUniform1i(dirLightCountLoc, directional_light_count_);
    glUniform1i(spotLightCountLoc, spotlight_light_count_);
}

const std::vector<std::shared_ptr<LightDirectional>>
LightGroup::GetDirectionalLights() const {
    std::vector<std::shared_ptr<LightDirectional>> out_lights;

    for(auto& light : lights_){
        if(light->light_type() == LightType::DIRECTIONAL){
            out_lights.push_back
                    (std::static_pointer_cast<LightDirectional>(light));
        }
    }

    return out_lights;
}

void LightGroup::Add(std::shared_ptr<LightSource> light_source){
    this->lights_.push_back(light_source);

    switch(light_source->light_type()){
        case LightType::SPOTLIGHT:
            spotlight_light_count_++;
            break;
        case LightType::DIRECTIONAL:
            directional_light_count_++;
            break;
        case LightType::POINT:
            point_light_count_++;
            break;
    }
}

bool LightGroup::Remove(std::shared_ptr<LightSource> light_source){
    for(unsigned int i = 0; i < lights_.size(); i++){
        if(lights_[i] == light_source){
            lights_.erase(lights_.begin() + i);

            switch(light_source->light_type()){
                case LightType::SPOTLIGHT:
                    spotlight_light_count_--;
                    break;
                case LightType::DIRECTIONAL:
                    directional_light_count_--;
                    break;
                case LightType::POINT:
                    point_light_count_--;
                    break;
            }

            return true;
        }
    }
    return false;
}
/*
void LightGroup::addLightPoint(std::unique_ptr<LightPoint> light){
    this->light_points_.push_back(light.get());

    this->all_lights_.push_back(std::move(light));
}

void LightGroup::addLightDirectional(std::unique_ptr<LightDirectional> light){
    this->light_directions_.push_back(light.get());

    this->all_lights_.push_back(std::move(light));
}

void LightGroup::addLightSpotlight(std::unique_ptr<LightSpotlight> light){
    this->light_spotlights_.push_back(light.get());

    this->all_lights_.push_back(std::move(light));
}
*/
void LightGroup::use(const Program& program){
    bindLightCount(program);

    int spotlights, points, directionals;
    spotlights = points = directionals = 0;

    for(auto& light : lights_){
        switch(light->light_type()){
            case LightType::SPOTLIGHT:
                light->use(program, spotlights++);
                break;
            case LightType::DIRECTIONAL:
                light->use(program, directionals++);
                break;
            case LightType::POINT:
                light->use(program, points++);
                break;
        }
    }
}

void LightGroup::render(const Program& program){
    for(auto& light : lights_)
        light->render(program);
}
