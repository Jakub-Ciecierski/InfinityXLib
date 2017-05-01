#include "graphics/lighting/types/light_directional.h"

#include <graphics/lighting/builders/dirlight_shader_builder.h>
#include <graphics/rendering/shadows/shadow_mapping.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/buffers/fbo.h>
#include <graphics/shaders/textures/texture.h>
#include <graphics/shaders/textures/texture_activator.h>
#include <graphics/shaders/loaders/program_loader.h>

using namespace ifx;

LightDirectional::LightDirectional(const LightParams& light_params) :
        LightSource(light_params, LightType::DIRECTIONAL){
    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("shadow_mapping/shadow_mapping.vs",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("shadow_mapping/shadow_mapping.fs",
                                      ifx::ResourceType::SHADER);
    auto program = ProgramLoader().CreateProgram(vertex_path, fragment_path);

    shadow_mapping_ = std::shared_ptr<ShadowMapping>(
            new ShadowMapping(Dimensions{4024, 4024}, program));
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
                       glm::value_ptr(
                               shadow_mapping_->GetLightSpaceMatrix(this)));

    if(cast_shadow_){
        int i = TextureActivator::GetInstance().GetNextGlobalID();
        glActiveTexture(GL_TEXTURE0 + i);
        shadow_mapping_->fbo()->texture()->Bind();
        glUniform1i(glGetUniformLocation(program.getID(),
                                         builder.SHADOW_MAP.c_str()), i);
    }
}

void LightDirectional::RenderToShadowMap(
        const std::shared_ptr<SceneRenderer> scene){
    if(cast_shadow_)
        shadow_mapping_->Render(scene, this);
}
