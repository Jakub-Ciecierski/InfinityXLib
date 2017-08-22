#include "game/factory/game_contexts_factory.h"

#include <graphics/rendering/context/factory/rendering_context_opengl_factory.h>

#include <controls/context/factory/control_context_glfw_factory.h>

#include <gui/context/factory/glfw/gui_glfw_context_factory.h>

#include <game/resources/factory/resource_context_factory.h>

namespace ifx{

GameContextsFactory::GameContextsFactory(){
    CreateDefaultFactories();
}

EngineContexts GameContextsFactory::Create(){
    EngineContexts engine_contexts;

    if(rendering_context_factory_) {
        engine_contexts.rendering_context
                = rendering_context_factory_->Create();
    }
    if(resource_context_factory_) {
        engine_contexts.resource_context =
                resource_context_factory_->Create();
    }
    if(control_context_factory_) {
        engine_contexts.control_context
                = control_context_factory_->Create();
    }
    if(gui_context_factory_) {
        engine_contexts.gui_context
                = gui_context_factory_->Create();
    }

    return engine_contexts;
}

void GameContextsFactory::CreateDefaultFactories(){
    rendering_context_factory_
            = std::make_shared<RenderingContextOpenglFactory>();

    resource_context_factory_ = std::make_shared<ResourceContextFactory>();

    control_context_factory_ = std::make_shared<ControlContextGLFWFactory>();

    gui_context_factory_ = std::make_shared<GUIGLFWContextFactory>();
}

GameContextsFactory& GameContextsFactory::SetRenderingContextFactory(
        std::shared_ptr<RenderingContextFactory> factory){
    rendering_context_factory_ = factory;
    return *this;
}

GameContextsFactory& GameContextsFactory::SetResourceContextFactory(
        std::shared_ptr<ResourceContextFactory> factory){
    resource_context_factory_ = factory;
    return *this;
}

GameContextsFactory& GameContextsFactory::SetControlContextFactory(
        std::shared_ptr<ControlContextFactory> factory){
    control_context_factory_ = factory;
    return *this;
}

GameContextsFactory &
GameContextsFactory::SetGUIContextFactory(
        std::shared_ptr<GUIContextFactory> factory) {
    gui_context_factory_ = factory;
    return *this;
}


}
