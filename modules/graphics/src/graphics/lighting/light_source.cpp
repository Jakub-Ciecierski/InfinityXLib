#include <graphics/lighting/light_source.h>

namespace ifx {

LightSource::LightSource(const LightParams& light_params, LightType type) :
        light_params_(light_params),
        light_type_(type),
        GameComponent(GameComponentType::LIGHT){
}

LightSource::~LightSource() {}

// static
std::string LightSource::LightTypeString(LightType type){
    switch(type){
        case LightType::DIRECTIONAL:
            return "Directional";
        case LightType::POINT:
            return "Point";
        case LightType::SPOTLIGHT:
            return "Spotlight";
    }
}

void LightSource::SetLightParams(const LightParams &light_params) {
    light_params_ = light_params;
}

void LightSource::use(const Program &program, int id) {
    program.use();

    bind(program, id);
}

void LightSource::render(const Program &program) {
    return;
}

} // ifx