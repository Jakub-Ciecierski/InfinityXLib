#include "graphics/rendering/shadows/shadow_mapping.h"

#include <graphics/lighting/light_group.h>
#include <graphics/lighting/types/light_directional.h>
#include <graphics/shaders/buffers/fbo.h>
#include <graphics/shaders/program.h>
#include <graphics/rendering/scene_renderer.h>

namespace ifx {

ShadowMapping::ShadowMapping(Dimensions dimensions,
                             std::shared_ptr<Program> program) :
        program_(program),
        dimensions_(dimensions){
    InitFBO(CreateTexture());
}

ShadowMapping::~ShadowMapping(){}

void ShadowMapping::Render(const std::shared_ptr<SceneRenderer> scene){
    glViewport(0, 0, dimensions_.width, dimensions_.height);

    const std::vector<std::shared_ptr<LightDirectional>> lights
            = scene->light_group()->GetDirectionalLights();
    for(unsigned int i = 0; i < lights.size(); i++){
        program_->use();
        BindLightMatrix(program_.get(), lights[i].get());

        fbo_->bind();
        glClear(GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_FRONT); // peter panning
        scene->Render(program_);
        glCullFace(GL_BACK); // peter panning
        fbo_->unbind();
    }

    glActiveTexture(GL_TEXTURE0);
    fbo_->texture()->Bind();
    glUniform1i(glGetUniformLocation(program_->getID(),
                                     TEXTURE_SHADOW_MAP.c_str()), 0);
}

std::shared_ptr<Texture2D> ShadowMapping::CreateTexture(){
    auto texture
            = Texture2D::MakeTexture2DEmpty("shadow_mapping",
                                            TextureTypes::FBO,
                                            TextureInternalFormat::DEPTH_COMPONENT,
                                            TexturePixelType::FLOAT,
                                            dimensions_.width,
                                            dimensions_.height);

    texture->AddParameter(TextureParameter{GL_TEXTURE_MIN_FILTER, GL_NEAREST});
    texture->AddParameter(TextureParameter{GL_TEXTURE_MAG_FILTER, GL_NEAREST});
    // Pixels outside shadow mapp range will have value indicating no shadow.
    texture->AddParameter(TextureParameter{GL_TEXTURE_WRAP_S,
                                           GL_CLAMP_TO_BORDER});
    texture->AddParameter(TextureParameter{GL_TEXTURE_WRAP_T,
                                           GL_CLAMP_TO_BORDER});
    texture->Bind();
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    texture->Unbind();

    return texture;
}

void ShadowMapping::InitFBO(std::shared_ptr<Texture2D> texture){
    fbo_.reset(new FBO(texture, FBOType::DEPTH));
    fbo_->compile();
}

void ShadowMapping::BindLightMatrix(const Program* program,
                                    LightDirectional* light){
    GLint lightSpaceMatrixLoc
            = glGetUniformLocation(program->getID(),
                                   LIGHT_SPACE_MATRIX_NAME.c_str());
    glm::mat4 mat = light->GetLightSpaceMatrix();
    glUniformMatrix4fv(lightSpaceMatrixLoc, 1, GL_FALSE,
                       glm::value_ptr(light->GetLightSpaceMatrix()));

}

} // ifx
