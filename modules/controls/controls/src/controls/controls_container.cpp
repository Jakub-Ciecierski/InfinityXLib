#include "controls/controls_container.h"

namespace ifx {

ControlsContainer::ControlsContainer() {}

ControlsContainer::~ControlsContainer() {}

ControlsContainer &ControlsContainer::GetInstance() {
    static ControlsContainer container;

    return container;
}

}
