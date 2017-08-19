#include "editor/editor_tool.h"

#include <editor/window_view.h>
#include <editor/docker.h>

namespace ifx{

EditorTool::EditorTool(std::shared_ptr<Docker> docker) :
        docker_(docker){}

void EditorTool::Render(){
    for(auto& view : window_views_){
        if(!view)
            continue;

        if(docker_)
            docker_->Dock(view);
        view->Render();
    }
}

void EditorTool::AddWindowView(std::shared_ptr<WindowView> view){
    window_views_.push_back(view);
}

}
