#include "editor/editor.h"

#include <editor/views/main_menu.h>
#include <editor/docker.h>

#include <gui/theme.h>

namespace ifx{

Editor::Editor(std::shared_ptr<Docker> docker) :
        docker_(docker){
    SetDefaultTheme();
}

Editor::~Editor(){}

void Editor::Render(){
    for(auto& view : views_){
        docker_->Dock(view);
        view->Render();
    }

}

void Editor::SetDefaultTheme(){
    GUIThemeDracula();
}

void Editor::AddView(std::shared_ptr<View> view) {
    views_.push_back(view);
}

}
