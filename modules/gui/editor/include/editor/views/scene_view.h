#ifndef PROJECT_SCENE_VIEW_H
#define PROJECT_SCENE_VIEW_H

#include <editor/view.h>

namespace ifx {

class SceneView : public View{
public:
    SceneView();
    ~SceneView() = default;

    virtual void Render() override;
};
}

#endif //PROJECT_SCENE_VIEW_H
