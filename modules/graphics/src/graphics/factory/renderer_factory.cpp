#include "graphics/factory/renderer_factory.h"

#include <graphics/rendering/renderer.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>

#include <graphics/factory/scene_factory.h>
#include <graphics/factory/program_factory.h>

namespace ifx {

RendererFactory::RendererFactory() { }

RendererFactory::~RendererFactory() { }

std::shared_ptr<Renderer> RendererFactory::Create() {
    auto renderer = std::unique_ptr<ifx::Renderer>(new ifx::Renderer());
    renderer->SetShadowsType(ifx::ShadowsType::SHADOW_MAPPING);
    ifx::Window *window = renderer->window();
    auto fbo_renderer = CreateFBORenderer(window);
    renderer->SetFBORenderer(std::move(fbo_renderer));
    renderer->SetShadowMapping(CreateShadowMapping());

    return renderer;
}

std::unique_ptr<FBORenderer> RendererFactory::CreateFBORenderer(
        Window *window) {
    auto fbo_renderer = std::unique_ptr<FBORenderer>(new FBORenderer(window));
    fbo_renderer->SetProgram(ProgramFactory().LoadFBOProgram());

    return fbo_renderer;
}

std::unique_ptr<ShadowMapping> RendererFactory::CreateShadowMapping() {
    std::shared_ptr<Program> program
            = ProgramFactory().LoadShadowMappingProgram();
    auto shadow_mapping = std::unique_ptr<ShadowMapping>(
            new ShadowMapping(Dimensions{4024, 4024}, program));
    return shadow_mapping;
};

}