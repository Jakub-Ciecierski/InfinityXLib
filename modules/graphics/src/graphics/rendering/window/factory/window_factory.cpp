#include "graphics/rendering/window/factory/window_factory.h"

#include "graphics/rendering/window/window.h"

namespace ifx {

WindowFactory::WindowFactory(std::string name,
                             int width, int height) :
        name_(name), width_(width), height_(height){}

WindowFactory::~WindowFactory(){}

std::shared_ptr<Window> WindowFactory::Create(){
    return std::shared_ptr<Window>(new Window(width_, height_, name_));
}

}