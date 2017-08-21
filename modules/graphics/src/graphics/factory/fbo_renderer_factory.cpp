#include "graphics/factory/fbo_renderer_factory.h"

#include <graphics/shaders/buffers/fbo.h>
#include <graphics/shaders/textures/texture.h>
#include <graphics/model/mesh.h>
#include "graphics/shaders/textures/texture_creator.h"
#include <graphics/rendering/window/window.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/shaders/loaders/program_loader.h>
#include <graphics/shaders/program_creator.h>

#include <resources/resource_manager.h>

#include <common/unique_ptr.h>

#include <GL/glew.h>

namespace ifx{

std::shared_ptr<Renderer> FBORendererFactory::Create(
        std::shared_ptr<Window> window,
        std::shared_ptr<RenderingContext> rendering_context,
        std::shared_ptr<TextureCreator> texture_creator,
        std::shared_ptr<ProgramCreator> program_creator,
        std::shared_ptr<ResourceManager> resource_manager){
    auto fbo = CreateFBO(window, texture_creator);
    auto screen_mesh = CreateScreenMesh(*fbo);
    auto program = CreateProgram(program_creator, resource_manager);

    auto fbo_renderer = std::make_shared<FBORenderer>(
            window,
            rendering_context,
            std::move(fbo), std::move(screen_mesh),
            program);

    return fbo_renderer;
}

std::unique_ptr<FBO> FBORendererFactory::CreateFBO(
        std::shared_ptr<Window> window,
        std::shared_ptr<TextureCreator> texture_creator){
    auto texture = texture_creator->MakeTexture2DEmpty(
            "fbo",
            TextureTypes::FBO,
            TextureInternalFormat::RGB,
            TexturePixelType::UNSIGNED_BYTE,
            *(window->width()), *(window->height()));

    texture->AddParameter(TextureParameter{GL_TEXTURE_MIN_FILTER, GL_LINEAR});
    texture->AddParameter(TextureParameter{GL_TEXTURE_MAG_FILTER, GL_LINEAR});

    auto fbo = ifx::make_unique<FBO>(texture,
                                     FBOType{FBOBuffer::COLOR_DEPTH,
                                             FBOAAColorBufferMultiplier::AA4});
    fbo->compile();

    return fbo;
}

std::unique_ptr<Mesh> FBORendererFactory::CreateScreenMesh(const FBO& fbo){
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

    auto screen_mesh = ifx::make_unique<Mesh>(vertices, indices);

    auto material = std::make_shared<Material>();
    material->AddTexture(fbo.texture());

    screen_mesh->material(material);
    return screen_mesh;
}

std::shared_ptr<Program> FBORendererFactory::CreateProgram(
        std::shared_ptr<ProgramCreator> program_creator,
        std::shared_ptr<ResourceManager> resource_manager){
    std::string vertex_path =
            resource_manager->resource_path()->GetResourcePath(
                    "engine/fbo.prog/fbo.vs", ifx::ResourceType::SHADER);
    std::string fragment_path =
            resource_manager->resource_path()->GetResourcePath(
                    "engine/fbo.prog/fbo.fs", ifx::ResourceType::SHADER);

    auto program = ProgramLoader(program_creator).CreateProgram(vertex_path,
                                                                fragment_path);
    return program;

}

};