#include "gui/factory/gui_factory.h"

#include "gui/gui.h"

namespace ifx {

std::shared_ptr<GUI> GUIFactory::Create(
        std::shared_ptr<GUIContext> context) {
    if(!context){
        throw std::invalid_argument(
                "Creating GUI System: Missing Dependencies");
    }

    auto gui = std::make_shared<GUI>(context);

    return gui;
}

}