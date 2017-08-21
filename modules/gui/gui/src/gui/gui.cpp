#include "gui/gui.h"

#include <gui/context/gui_context.h>
#include <gui/gui_part.h>
#include <controls/context/control_context.h>

namespace ifx {

GUI::GUI(std::shared_ptr<GUIContext> context) :
        context_(context),
        is_init_(false) {}

GUI::~GUI() {}

void GUI::Update(float time_delta) {
    context_->NewFrame();

    for(auto& gui_part : gui_parts_)
        gui_part->Render();

    context_->Render();
}

bool GUI::Init(void *native_window,
               std::shared_ptr<ControlContext> control_context) {
    if(!native_window || !control_context){
        throw std::invalid_argument(
                "Creating GUI System: Missing Dependencies");
    }
    return context_->Init(native_window, control_context);
}

bool GUI::Terminate() {
    return context_->Terminate();
}

void GUI::AddGUIPart(std::shared_ptr<GUIPart> gui_part) {
    gui_parts_.push_back(gui_part);
}

}