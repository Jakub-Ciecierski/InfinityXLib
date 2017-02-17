#ifndef PROJECT_ENGINE_GUI_H
#define PROJECT_ENGINE_GUI_H

#include <memory>

namespace ifx{

class MainMenu;
class SceneView;
class PhysicsSimulationView;
class ImGuiDemoView;

struct EngineGUICreateParams {
    std::shared_ptr<MainMenu> main_menu;
    std::shared_ptr<SceneView> scene_view;
    std::shared_ptr<PhysicsSimulationView> physics_simulation_view;
    std::shared_ptr<ImGuiDemoView> imgui_demo_view;
};

class EngineGUI {
public:
    EngineGUI(EngineGUICreateParams& create_params);
    ~EngineGUI();

    std::shared_ptr<SceneView> scene_view(){return scene_view_;}

    /**
     * Renders windows and other non scene related stuff.
     */
    void Render();

    /**
     * Renders scene objects e.g. manipulator.
     */
    void RenderSceneObjects();

private:
    void SetDefaultTheme();

    std::shared_ptr<MainMenu> main_menu_;
    std::shared_ptr<SceneView> scene_view_;
    std::shared_ptr<PhysicsSimulationView> physics_simulation_view_;
    std::shared_ptr<ImGuiDemoView> imgui_demo_view_;
};

}

#endif //PROJECT_ENGINE_GUI_H

