#ifndef PROJECT_SCENE_FACTORY_H
#define PROJECT_SCENE_FACTORY_H

#include <memory>

namespace ifx {

class Camera;
class Window;

class SceneFactory {
public:

    SceneFactory();
    ~SceneFactory();

    std::shared_ptr<Camera> CreateCamera(Window* window);

private:
};

}

#endif //PROJECT_SCENE_FACTORY_H
