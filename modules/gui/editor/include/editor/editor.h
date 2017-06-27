#ifndef PROJECT_ENGINE_GUI_H
#define PROJECT_ENGINE_GUI_H

#include <gui/gui_part.h>

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

class Editor : public GUIPart {
public:
    Editor(EngineGUICreateParams& create_params);
    ~Editor();

    std::shared_ptr<SceneView> scene_view(){return scene_view_;}

    /**
     * Renders windows and other non scene related stuff.
     */
    virtual void Render() override;

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

