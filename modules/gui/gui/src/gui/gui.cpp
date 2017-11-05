#include "gui/gui.h"

#include <gui/context/gui_context.h>
#include <gui/gui_part.h>

#include <controls/context/control_context.h>

namespace ifx {

GUI::GUI(std::shared_ptr<GUIContext> context) :
    context_(context),
    is_init_(false) {}

void GUI::UpdateFixedContent() {
    context_->NewFrame();

    for (auto &gui_part : gui_parts_)
        gui_part->Render();

    context_->Render();
}

bool GUI::Terminate() {
    for (auto &gui_part : gui_parts_) {
        if (!gui_part->Terminate())
            return false;
    }
    return true;
}

void GUI::AddGUIPart(std::shared_ptr<GUIPart> gui_part) {
    gui_parts_.push_back(gui_part);
}

}