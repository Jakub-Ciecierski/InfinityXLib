#ifndef PROJECT_ENGINE_GUI_H
#define PROJECT_ENGINE_GUI_H

#include <memory>

namespace ifx{

class MainMenu;
class SceneView;

struct EngineGUICreateParams {
    std::shared_ptr<MainMenu> main_menu;
    std::shared_ptr<SceneView> scene_view;
};

class EngineGUI {
public:
    EngineGUI(EngineGUICreateParams& create_params);
    ~EngineGUI();

    void Render();

private:
    std::shared_ptr<MainMenu> main_menu_;
    std::shared_ptr<SceneView> scene_view_;
};

}

#endif //PROJECT_ENGINE_GUI_H
