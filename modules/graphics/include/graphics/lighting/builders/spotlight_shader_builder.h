#ifndef DUCK_SPOTLIGHT_SHADER_BUILDER_H
#define DUCK_SPOTLIGHT_SHADER_BUILDER_H

#include "graphics/lighting/builders/light_shader_builder.h"

namespace ifx {
    /*
     * Builds strings for binding with spotlight in fragment shader
     */
    class SpotLightShaderBuilder : public LightShaderBuilder{


    public:
        std::string POSITION;
        std::string DIRECTION;

        std::string CUTOFF;
        std::string OUTCUTOFF;

        std::string AMBIENT;
        std::string DIFFUSE;
        std::string SPECULAR;

        std::string ATTEN_CONSTANT;
        std::string ATTEN_LINEAR;
        std::string ATTEN_QUAD;

        std::string LIGHT_SPACE_MATRIX;
        std::string SHADOW_MAP;

        SpotLightShaderBuilder(int id);

        virtual void build() override;
    };
}

#endif //DUCK_SPOTLIGHT_SHADER_BUILDER_H
