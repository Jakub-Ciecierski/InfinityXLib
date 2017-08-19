#ifndef PROJECT_ENGINE_GUI_H
#define PROJECT_ENGINE_GUI_H

#include <gui/gui_part.h>

#include <memory>
#include <vector>

namespace ifx{

class MainMenuWindowView;
class SceneView;
class ImGuiDemoWindowView;
class Docker;
class WindowView;

class Editor : public GUIPart {
public:
    Editor(std::shared_ptr<Docker> docker);
    ~Editor();

    std::shared_ptr<Docker> docker(){return docker_;}

    const std::vector<std::shared_ptr<WindowView>>& window_views(){return window_views_;}

    /**
     * Renders windows and other non scene related stuff.
     */
    virtual void Render() override;

    void AddWindowView(std::shared_ptr<WindowView> view);

private:
    void SetDefaultTheme();

    std::shared_ptr<Docker> docker_;

    std::vector<std::shared_ptr<WindowView>> window_views_;
};

}

#endif //PROJECT_ENGINE_GUI_H

