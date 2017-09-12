#include "controls/factory/controls_factory.h"

#include <controls/controller/factory/controller_container_factory.h>
#include <controls/controls.h>

namespace ifx {

ControlsFactory::ControlsFactory() {
    CreateDefaultFactories();
}

ControlsFactory::~ControlsFactory() {}

std::shared_ptr<Controls> ControlsFactory::Create(
    std::shared_ptr<ControlContext> control_context) {
    if (!control_context) {
        throw std::invalid_argument(
            "Creating Controls System: Missing Dependencies");
    }

    auto input_container = controller_container_factory_->Create();

    auto controls = std::make_shared<Controls>(control_context,
                                               input_container);

    return controls;
}

void ControlsFactory::CreateDefaultFactories() {
    controller_container_factory_
        = std::make_shared<ControllerContainerFactory>();
}

}