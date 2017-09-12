#include "editor/view.h"

namespace ifx {

View::View(std::string name) :
    name_(name),
    is_window_focused_(false) {}

bool View::Terminate() {
    return true;
}

}