#ifndef PROJECT_ENGINE_GUI_H
#define PROJECT_ENGINE_GUI_H

#include <gui/gui_part.h>

#include <memory>
#include <vector>

namespace ifx{

class MainMenu;
class SceneView;
class PhysicsSimulationView;
class ImGuiDemoView;
class Docker;
class View;

class Editor : public GUIPart {
public:
    Editor(std::shared_ptr<Docker> docker);
    ~Editor();

    std::shared_ptr<Docker> docker(){return docker_;}

    const std::vector<std::shared_ptr<View>>& views(){return views_;}

    /**
     * Renders windows and other non scene related stuff.
     */
    virtual void Render() override;

    void AddView(std::shared_ptr<View> view);

private:
    void SetDefaultTheme();

    std::shared_ptr<Docker> docker_;

    std::vector<std::shared_ptr<View>> views_;
};

}

#endif //PROJECT_ENGINE_GUI_H

