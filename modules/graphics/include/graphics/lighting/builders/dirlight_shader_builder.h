#ifndef DUCK_DIRLIGHT_SHADER_BUILDER_H
#define DUCK_DIRLIGHT_SHADER_BUILDER_H

#include "graphics/lighting/builders/light_shader_builder.h"

namespace ifx {

class DirlightShaderBuilder : public LightShaderBuilder {
public:
    std::string DIRECTION;

    std::string AMBIENT;
    std::string DIFFUSE;
    std::string SPECULAR;

    std::string LIGHT_SPACE_MATRIX;

    std::string SHADOW_MAP;

    DirlightShaderBuilder(int id);

    ~DirlightShaderBuilder();

    virtual void build() override;
};
}

#endif //DUCK_DIRLIGHT_SHADER_BUILDER_H
