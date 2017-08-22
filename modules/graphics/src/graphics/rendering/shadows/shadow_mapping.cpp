#include "graphics/rendering/shadows/shadow_mapping.h"

#include <graphics/lighting/light_group.h>
#include <graphics/lighting/types/light_spotlight.h>
#include <graphics/shaders/buffers/fbo.h>
#include <graphics/rendering/scene_renderer.h>
#include <graphics/shaders/textures/texture_creator.h>

#include <common/unique_ptr.h>

#include <GL/glew.h>

namespace ifx {

ShadowMapping::ShadowMapping(Dimensions dimensions,
                             std::shared_ptr<Program> program,
                             std::shared_ptr<TextureCreator> texture_creator) :
        program_(program),
        dimensions_(dimensions),
        texture_creator_(texture_creator){
    InitFBO(CreateTexture());
}

ShadowMapping::~ShadowMapping(){}

void ShadowMapping::Render(const std::shared_ptr<SceneRenderer> scene,
                           LightDirectional* light){
    glViewport(0, 0, dimensions_.width, dimensions_.height);

    program_->use();
    BindLightMatrix(program_.get(), light);

    fbo_->Bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT); // peter panning
    scene->Render(program_);
    glCullFace(GL_BACK); // peter panning
    fbo_->Unbind();
}

std::shared_ptr<Texture2D> ShadowMapping::CreateTexture(){
    auto texture
            = texture_creator_->MakeTexture2DEmpty(
                    NO_FILEPATH,
                    TextureTypes::FBO,
                    TextureInternalFormat::DEPTH_COMPONENT,
                    TexturePixelType::FLOAT,
                    dimensions_.width, dimensions_.height);
    texture->InitData();

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
    fbo_ = ifx::make_unique<FBO>(texture,
                                 FBOType{FBOBuffer::DEPTH,
                                         FBO_MSAA::NONE});

    fbo_->Compile();
}

void ShadowMapping::Reset(Dimensions&& new_dimensions){
    dimensions_ = new_dimensions;
    InitFBO(CreateTexture());
}

void ShadowMapping::BindLightMatrix(const Program* program,
                                    LightDirectional* light){
    GLint lightSpaceMatrixLoc
            = glGetUniformLocation(program->getID(),
                                   LIGHT_SPACE_MATRIX_NAME.c_str());
    glUniformMatrix4fv(lightSpaceMatrixLoc, 1, GL_FALSE,
                       glm::value_ptr(GetLightSpaceMatrix(light)));

}

glm::mat4 ShadowMapping::GetLightSpaceMatrix(LightDirectional* light) {
    glm::mat4 light_projection
            = glm::ortho(projection_parameters_.left,
                         projection_parameters_.right,
                         projection_parameters_.bottom,
                         projection_parameters_.up,
                         projection_parameters_.near_plane,
                         projection_parameters_.far_plane);
    const glm::vec3 UP = glm::vec3(0.01f, 1.0f, 0.01f);

    auto& position = light->getPosition();
    auto& direction = light->getDirection();
    glm::mat4 light_view = glm::lookAt(position,
                                       position + direction,
                                       UP);

    return light_projection * light_view;
}

} // ifx

