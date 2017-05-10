#include "controls/controller/controllers/factory/mouse_controller_factory.h"

#include <controls/controller/controllers/mouse_controller.h>
#include <controls/controller/events/mouse_controller_event.h>
#include <controls/controller/events/mouse_scroll_controller_event.h>
#include <controls/controller/controller_types.h>

namespace ifx {

MouseControllerFactory::MouseControllerFactory(){}
MouseControllerFactory::~MouseControllerFactory(){}

std::shared_ptr<MouseController> MouseControllerFactory::Create(){
    MouseControllerEvents events{
            std::make_shared<MouseControllerEvent>(
                    MouseControllerKeyType::MOUSE_LEFT),
            std::make_shared<MouseControllerEvent>(
                    MouseControllerKeyType::MOUSE_RIGHT),
            std::make_shared<MouseControllerEvent>(
                    MouseControllerKeyType::MOUSE_MIDDLE),
            std::make_shared<MouseScrollControllerEvent>()
    };

    auto mouse_input = std::make_shared<MouseController>(std::move(events));

    return mouse_input;
}

}