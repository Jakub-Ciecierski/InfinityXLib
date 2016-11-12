#ifndef PROJECT_SCENE_GUI_H
#define PROJECT_SCENE_GUI_H

#include <memory>
#include <vector>

namespace ifx {

class Scene;
class RenderObject;

class SceneWindowGUI {
public:

    SceneWindowGUI(std::shared_ptr<Scene> scene);
    ~SceneWindowGUI();

    void Render();

private:
    void RenderWindow();

    void RenderObjectInfo(std::shared_ptr<RenderObject> render_object);

    void RenderTransform(std::shared_ptr<RenderObject> render_object);
    void RenderPosition(std::shared_ptr<RenderObject> render_object);
    void RenderRotation(std::shared_ptr<RenderObject> render_object);
    void RenderScale(std::shared_ptr<RenderObject> render_object);

    void RenderProperties(std::shared_ptr<RenderObject> render_object);

    std::shared_ptr<Scene> scene_;

    std::vector<const char*> display_names_;
    int scene_listbox_item_current_;

};
}

#endif //PROJECT_SCENE_GUI_H
