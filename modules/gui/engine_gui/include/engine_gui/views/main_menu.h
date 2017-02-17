#ifndef PROJECT_MAIN_MENU_H
#define PROJECT_MAIN_MENU_H

#include <engine_gui/view.h>
#include <memory>

namespace ifx{

class SceneView;
class PhysicsSimulationView;
class ImGuiDemoView;

class MainMenu : public View {
public:
    MainMenu(std::shared_ptr<SceneView> scene_view,
             std::shared_ptr<PhysicsSimulationView> physics_simulation_view,
             std::shared_ptr<ImGuiDemoView> imgui_demo_view);
    ~MainMenu();

    // overridden from View
    void Render() override;

private:
    void RenderFile();
    void RenderEdit();
    void RenderView();
    void RenderWindow();

    std::shared_ptr<SceneView> scene_view_;
    std::shared_ptr<PhysicsSimulationView> physics_simulation_view_;
    std::shared_ptr<ImGuiDemoView> imgui_demo_view_;
};

}

#endif //PROJECT_MAIN_MENU_H
