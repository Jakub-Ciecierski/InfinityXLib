#include "graphics/rendering/window/factory/window_factory.h"

#include "graphics/rendering/window/window.h"

namespace ifx {

WindowFactory::WindowFactory(std::string name,
                             int width, int height) :
        name_(name), width_(width), height_(height){}

WindowFactory::~WindowFactory(){}

std::shared_ptr<Window> WindowFactory::Create(
        std::shared_ptr<RenderingContext> rendering_context,
        std::shared_ptr<ControlContext> control_context){
    auto window = std::make_shared<Window>(width_, height_, name_);

    if(!window->Init(rendering_context, control_context)){
        throw new std::invalid_argument("window->Init Failed");
    }

    return window;
}

}