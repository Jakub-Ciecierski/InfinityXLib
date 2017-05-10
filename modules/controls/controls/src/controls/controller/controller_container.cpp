#include "controls/controller/controller_container.h"

#include <controls/controller/controllers/keyboard_controller.h>
#include <controls/controller/controllers/mouse_controller.h>

namespace ifx {

ControllerContainer::ControllerContainer(
        std::shared_ptr<MouseController>mouse_input,
        std::shared_ptr<KeyboardController> keyboard_input) :
        mouse_controller_(mouse_input),
        keyboard_controller_(keyboard_input){}

ControllerContainer::~ControllerContainer(){}

void ControllerContainer::Update(float){
    mouse_controller_->Update();
    keyboard_controller_->Update();
}

}