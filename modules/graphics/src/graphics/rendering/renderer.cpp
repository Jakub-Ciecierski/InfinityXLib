#include "graphics/rendering/renderer.h"

#include <graphics/shaders/program.h>
#include <controls/glfw_callbacks.h>
#include <controls/controls_events.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/scene_renderer.h>
#include <gui/gui.h>
#include <resources/resource_memory_cache.h>

namespace ifx {

Renderer::Renderer() :
    rendering_type_(RenderingType::NORMAL),
    fbo_renderer_(nullptr){
    initGLFWRenderContext();
    initOpenGLContext();
    initGLFWCallbacks();

    scene_renderer_ = std::shared_ptr<SceneRenderer>(new SceneRenderer());
}

Renderer::~Renderer(){
    // TODO Resources requires GL context
    ResourceMemoryCache::GetInstance().ClearAll();
}

void Renderer::HandleEvents() {
    ControlsEvents& controls = ControlsEvents::GetInstance();
    const Keys& keys = controls.keyboard_keys();

    if (keys[GLFW_KEY_R]){
        auto programs = ResourceMemoryCache::GetInstance().GetResources(
                ResourceType::SHADER);
        for(auto& program : programs){
            std::static_pointer_cast<Program>(program)->Reload();
        }
    }
}

void Renderer::SetGUI(std::shared_ptr<GUI> gui){
    gui_ = gui;
}

void Renderer::SetRenderingType(RenderingType type){
    rendering_type_ = type;
}

void Renderer::SetShadowsType(ShadowsType type){
    shadow_type_ = type;
}

void Renderer::SetFBORenderer(std::unique_ptr<FBORenderer> fbo_renderer){
    fbo_renderer_ = std::move(fbo_renderer);
}

void Renderer::SetShadowMapping(std::unique_ptr<ShadowMapping> shadow_mapping){
    shadow_mapping_ = std::move(shadow_mapping);
}

void Renderer::LimitFPS(bool val){
    if(val)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

void Renderer::initGLFWRenderContext(){
    glfwInit();
    // OpenGL version required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // No legacy functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int width = 1500;
    int height = 1000;
    window_ .reset(new Window(width, height, "InfinityX"));

    LimitFPS(false);
}

void Renderer::initOpenGLContext(){
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw new std::invalid_argument("Failed to initialize GLEW");
}

void Renderer::initGLFWCallbacks(){
    glfwSetKeyCallback(window_->getHandle(), key_callback);
    glfwSetCursorPosCallback(window_->getHandle(), mouse_callback);
    glfwSetMouseButtonCallback(window_->getHandle(), mouse_button_callback);
    glfwSetScrollCallback(window_->getHandle(), mousescroll_callback);
    glfwSetCharCallback(window_->getHandle(), char_callback);
}

void Renderer::Render(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(rendering_type_ == RenderingType::NORMAL)
        RenderNormal();
    if(rendering_type_ == RenderingType::FBO_TEXTURE)
        RenderFBOTexture();

    if(gui_)
        gui_->Render();

    glfwSwapBuffers(window_->getHandle());

    window_->update();
    HandleEvents();
}

void Renderer::RenderNormal(){
    if(shadow_type_ == ShadowsType::NONE)
        RenderNormalNoShadow();
    if(shadow_type_ == ShadowsType::SHADOW_MAPPING)
        RenderNormalShadowMapping();
}

void Renderer::RenderNormalNoShadow(){
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    scene_renderer_->Render();
}

void Renderer::RenderNormalShadowMapping(){
    shadow_mapping_->Render(scene_renderer_);

    // Shadow mapping binds its own FBO
    if(rendering_type_ == RenderingType::FBO_TEXTURE)
        fbo_renderer_->Bind();

    glViewport(0, 0, *(window_->width()), *(window_->height()));
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    scene_renderer_->Render();
}

void Renderer::RenderFBOTexture(){
    if(!fbo_renderer_)
        return;
    // First Pass
    fbo_renderer_->Bind();
    RenderNormal();

    // Second Pass
    glDisable(GL_DEPTH_TEST);
    fbo_renderer_->Render();
}

}