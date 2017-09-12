#include "controls/controller/controllers/factory/keyboard_controller_factory.h"

#include <controls/controller/controllers/keyboard_controller.h>
#include <controls/controller/controller_types.h>
#include <controls/controller/events/keyboard_controller_event.h>

namespace ifx {

KeyboardControllerFactory::KeyboardControllerFactory() {}

KeyboardControllerFactory::~KeyboardControllerFactory() {}

std::shared_ptr<KeyboardController> KeyboardControllerFactory::Create() {
    auto NewKeyboardEvent = [](const KeyboardControllerKeyType &&type) ->
        std::shared_ptr<KeyboardControllerEvent> {
        return std::make_shared<KeyboardControllerEvent>(std::move(type));
    };

    std::vector<std::shared_ptr<KeyboardControllerEvent>> keyboard_events;

    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::Q));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::W));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::E));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::R));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::T));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::Y));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::U));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::I));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::O));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::P));

    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::A));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::S));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::D));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::F));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::G));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::H));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::J));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::K));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::L));

    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::Z));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::X));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::C));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::V));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::B));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::N));
    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::M));

    keyboard_events.push_back(NewKeyboardEvent(KeyboardControllerKeyType::UP));
    keyboard_events
        .push_back(NewKeyboardEvent(KeyboardControllerKeyType::DOWN));
    keyboard_events
        .push_back(NewKeyboardEvent(KeyboardControllerKeyType::LEFT));
    keyboard_events
        .push_back(NewKeyboardEvent(KeyboardControllerKeyType::RIGHT));

    keyboard_events
        .push_back(NewKeyboardEvent(KeyboardControllerKeyType::SPACE));
    keyboard_events
        .push_back(NewKeyboardEvent(KeyboardControllerKeyType::ENTER));

    auto keyboard_input = std::make_shared<KeyboardController>(keyboard_events);

    return keyboard_input;
}

}