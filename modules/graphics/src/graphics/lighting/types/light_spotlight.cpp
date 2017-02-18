#include <graphics/lighting/types/light_spotlight.h>
#include <graphics/lighting/builders/spotlight_shader_builder.h>
#include <graphics/rendering/shadows/shadow_mapping.h>
#include <graphics/shaders/buffers/fbo.h>
#include <graphics/shaders/textures/texture.h>

namespace ifx {

LightSpotlight::LightSpotlight(const LightParams& light_params) :
        LightDirectional(light_params){
    light_type_ = LightType::SPOTLIGHT;
}

LightSpotlight::~LightSpotlight() {}

void LightSpotlight::bind(const Program &program, int id) {
    ifx::SpotLightShaderBuilder builder(id);
    builder.build();

    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             builder.POSITION.c_str());

    GLint lightDirLoc = glGetUniformLocation(program.getID(),
                                             builder.DIRECTION.c_str());

    GLint lightAmbientLoc = glGetUniformLocation(program.getID(),
                                                 builder.AMBIENT.c_str());
    GLint lightDiffuseLoc = glGetUniformLocation(program.getID(),
                                                 builder.DIFFUSE.c_str());
    GLint lightSpecularLoc = glGetUniformLocation(program.getID(),
                                                  builder.SPECULAR.c_str());

    GLint attenConstLoc = glGetUniformLocation(program.getID(),
                                               builder.ATTEN_CONSTANT.c_str());
    GLint attenLineLoc = glGetUniformLocation(program.getID(),
                                              builder.ATTEN_LINEAR.c_str());
    GLint attenQuadLoc = glGetUniformLocation(program.getID(),
                                              builder.ATTEN_QUAD.c_str());

    // Light Cutoff
    GLint lightCutoffLoc = glGetUniformLocation(program.getID(),
                                                builder.CUTOFF.c_str());

    GLint lightOuterCutoffLoc = glGetUniformLocation(program.getID(),
                                                     builder.OUTCUTOFF.c_str());
    auto& position = getPosition();
    auto& direction = getDirection();
    glUniform3f(lightPosLoc, position.x, position.y, position.z);
    glUniform3f(lightDirLoc, direction.x, direction.y, direction.z);

    glUniform3f(lightAmbientLoc,
                light_params_.ambient.x,
                light_params_.ambient.y,
                light_params_.ambient.z);
    glUniform3f(lightDiffuseLoc,
                light_params_.diffuse.x,
                light_params_.diffuse.y,
                light_params_.diffuse.z);
    glUniform3f(lightSpecularLoc,
                light_params_.specular.x,
                light_params_.specular.y,
                light_params_.specular.z);

    glUniform1f(attenConstLoc, light_params_.constant);
    glUniform1f(attenLineLoc, light_params_.linear);
    glUniform1f(attenQuadLoc, light_params_.quadratic);

    glUniform1f(lightOuterCutoffLoc,
                glm::cos(glm::radians(light_params_.outerCutOff)));
    glUniform1f(lightCutoffLoc,
                glm::cos(glm::radians(light_params_.cutOff)));

    GLint lightSpaceMatrixLoc
            = glGetUniformLocation(program.getID(),
                                   builder.LIGHT_SPACE_MATRIX.c_str());
    glUniformMatrix4fv(lightSpaceMatrixLoc, 1, GL_FALSE,
                       glm::value_ptr(GetLightSpaceMatrix()));

    int i = 1 + id;
    glActiveTexture(GL_TEXTURE1 + id);
    shadow_mapping_->fbo()->texture()->Bind();
    glUniform1i(glGetUniformLocation(program.getID(),
                                     builder.SHADOW_MAP.c_str()), i);

}
}