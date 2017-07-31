#include "editor/editor.h"

#include <editor/window_view.h>
#include <editor/docker.h>

#include <gui/theme.h>

namespace ifx{

Editor::Editor(std::shared_ptr<Docker> docker) :
        docker_(docker){
    SetDefaultTheme();
}

Editor::~Editor(){}

void Editor::Render(){
    for(auto& view : window_views_){
        docker_->Dock(view);
        view->Render();
    }

}

void Editor::SetDefaultTheme(){
    GUIThemeDracula();
}

void Editor::AddWindowView(std::shared_ptr<WindowView> view) {
    window_views_.push_back(view);
}

}
