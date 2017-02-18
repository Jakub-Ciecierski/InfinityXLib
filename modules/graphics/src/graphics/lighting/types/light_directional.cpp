#include "graphics/lighting/types/light_directional.h"

#include <graphics/lighting/builders/dirlight_shader_builder.h>
#include <graphics/factory/program_factory.h>
#include <graphics/rendering/shadows/shadow_mapping.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/buffers/fbo.h>
#include <graphics/shaders/textures/texture.h>

using namespace ifx;

LightDirectional::LightDirectional(const LightParams& light_params) :
        LightSource(light_params, LightType::DIRECTIONAL){
    shadow_mapping_ = std::shared_ptr<ShadowMapping>(
            new ShadowMapping(Dimensions{4024, 4024},
                              ProgramFactory().LoadShadowMappingProgram()));
}

LightDirectional::~LightDirectional() {}

void LightDirectional::bind(const Program &program, int id) {
    ifx::DirlightShaderBuilder builder(id);
    builder.build();

    GLint lightDirLoc = glGetUniformLocation(program.getID(),
                                             builder.DIRECTION.c_str());
    GLint lightAmbientLoc  = glGetUniformLocation(program.getID(),
                                                  builder.AMBIENT.c_str());
    GLint lightDiffuseLoc  = glGetUniformLocation(program.getID(),
                                                  builder.DIFFUSE.c_str());
    GLint lightSpecularLoc = glGetUniformLocation(program.getID(),
                                                  builder.SPECULAR.c_str());
    GLint lightSpaceMatrixLoc
            = glGetUniformLocation(program.getID(),
                                   builder.LIGHT_SPACE_MATRIX.c_str());

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
    auto& direction = getDirection();
    glUniform3f(lightDirLoc, direction.x, direction.y, direction.z);
    glUniformMatrix4fv(lightSpaceMatrixLoc, 1, GL_FALSE,
                       glm::value_ptr(GetLightSpaceMatrix()));

    glActiveTexture(GL_TEXTURE0 + id);
    shadow_mapping_->fbo()->texture()->Bind();
    glUniform1i(glGetUniformLocation(program.getID(),
                                     builder.SHADOW_MAP.c_str()), id);
}

void LightDirectional::RenderToShadowMap(
        const std::shared_ptr<SceneRenderer> scene){
    shadow_mapping_->Render(scene, this);
}

glm::mat4 LightDirectional::GetLightSpaceMatrix() {
    GLfloat near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,
                                             near_plane, far_plane);
    const glm::vec3 UP = glm::vec3(0.01f, 1.0f, 0.01f);

    auto& position = getPosition();
    auto& direction = getDirection();
    glm::mat4 light_view = glm::lookAt(position,
                                       position + direction,
                                       UP);

    return light_projection * light_view;
}