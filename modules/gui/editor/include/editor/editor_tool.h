#ifndef PROJECT_EDITOR_TOOL_H
#define PROJECT_EDITOR_TOOL_H

#include <memory>
#include <vector>

namespace ifx {

class Docker;
class WindowView;

class EditorTool {
public:
    EditorTool(std::shared_ptr<Docker> docker);
    ~EditorTool() = default;

    const std::vector<std::shared_ptr<WindowView>>& window_views(){
        return window_views_;}

    void Render();

    void AddWindowView(std::shared_ptr<WindowView> view);
private:
    std::shared_ptr<Docker> docker_;

    std::vector<std::shared_ptr<WindowView>> window_views_;
};
}

#endif //PROJECT_EDITOR_TOOL_H
