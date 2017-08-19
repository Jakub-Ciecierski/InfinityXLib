#include "gui/factory/gui_factory.h"

#include "gui/gui.h"

namespace ifx {

GUIFactory::GUIFactory() {}

GUIFactory::~GUIFactory() {}

std::shared_ptr<GUI> GUIFactory::Create(
        std::shared_ptr<GUIContext> context) {
    return std::make_shared<GUI>(context);
}

}