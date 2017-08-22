#ifndef PROJECT_FBO_RENDERER_FACTORY_H
#define PROJECT_FBO_RENDERER_FACTORY_H

#include <memory>


#include "graphics/factory/renderer_factory.h"

namespace ifx {

class FBO;
class Mesh;
class TextureCreator;
class Program;

class FBORendererFactory : public RendererFactory {
public:
    FBORendererFactory() = default;
    ~FBORendererFactory() = default;

    virtual std::shared_ptr<Renderer> Create(
            std::shared_ptr<Window> window,
            std::shared_ptr<RenderingContext> rendering_context,
            std::shared_ptr<TextureCreator> texture_creator,
            std::shared_ptr<ProgramCreator> program_creator,
            std::shared_ptr<ResourceManager> resource_manager) override;
private:
    std::unique_ptr<FBO> CreateFBO(
            std::shared_ptr<Window> window,
            std::shared_ptr<TextureCreator> texture_creator);
    std::unique_ptr<FBO> CreateIntermediateFBO(
            std::shared_ptr<Window> window,
            std::shared_ptr<TextureCreator> texture_creator);

    std::unique_ptr<Mesh> CreateScreenMesh(const FBO& fbo);
    std::shared_ptr<Program> CreateProgram(
            std::shared_ptr<ProgramCreator> program_creator,
            std::shared_ptr<ResourceManager> resource_manager);
};

}

#endif //PROJECT_FBO_RENDERER_FACTORY_H
