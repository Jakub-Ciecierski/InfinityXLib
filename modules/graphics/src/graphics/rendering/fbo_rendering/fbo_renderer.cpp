#include "graphics/rendering/fbo_rendering/fbo_renderer.h"

#include <math/math_ifx.h>
#include <graphics/shaders/buffers/fbo.h>
#include <graphics/model/mesh.h>
#include <graphics/rendering/window/window.h>
#include <graphics/shaders/textures/texture.h>

namespace ifx {

FBORenderer::FBORenderer(Window* window) :
        program_(nullptr){
    initFBO(window);
    initScreenMesh();
}

FBORenderer::~FBORenderer(){}

void FBORenderer::SetProgram(std::shared_ptr<Program> program){
    program_ = program;
}

void FBORenderer::Bind(){
    fbo_->bind();
}

void FBORenderer::Render(){
    Render(program_.get());
}

void FBORenderer::Render(Program* program){
    if (!program_)
        return;

    fbo_->unbind();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    screenMesh_->draw(*program);
}

void FBORenderer::initFBO(Window* window){
    auto texture = Texture2D::MakeTexture2DEmpty(
            "fbo",
            TextureTypes::FBO,
            TextureInternalFormat::RGB,
            TexturePixelType::UNSIGNED_BYTE,
            *(window->width()), *(window->height()));

    texture->AddParameter(TextureParameter{GL_TEXTURE_MIN_FILTER, GL_LINEAR});
    texture->AddParameter(TextureParameter{GL_TEXTURE_MAG_FILTER, GL_LINEAR});

    fbo_ = std::unique_ptr<FBO>(new FBO(texture, FBOType::COLOR_DEPTH));
    fbo_->compile();
}

void FBORenderer::initScreenMesh(){
    // The position is in Normalized Device Coordinates.
    std::vector <Vertex> vertices = {
            Vertex{glm::vec3(1.0f, 1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(1.0f, -1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, -1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, 1.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
    };
    std::vector <GLuint> indices = { 0, 1, 3, 1, 2, 3 };

    screenMesh_ = std::unique_ptr<Mesh>(new Mesh(vertices, indices));

    auto material = std::make_shared<Material>();
    material->AddTexture(fbo_->texture());
    screenMesh_->material(material);
}

}
