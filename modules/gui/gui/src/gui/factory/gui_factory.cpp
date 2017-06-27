#include "gui/factory/gui_factory.h"

#include "gui/gui.h"

namespace ifx {

ifx::GUIFactory::GUIFactory() {}

ifx::GUIFactory::~GUIFactory() {}

std::shared_ptr<ifx::GUI> ifx::GUIFactory::Create(
        std::shared_ptr<GUIContext> context) {
    return std::make_shared<GUI>(context);
}

}