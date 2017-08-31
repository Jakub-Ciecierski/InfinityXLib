#ifndef PROJECT_SOFT_BODY_SCREEN_VIEW_H
#define PROJECT_SOFT_BODY_SCREEN_VIEW_H

#include <memory>

namespace ifx {

class Renderer;

class SoftBodyScreenView {
public:
    SoftBodyScreenView() = default;
    ~SoftBodyScreenView() = default;

    void Render(std::shared_ptr<Renderer> renderer);
private:
};

}

#endif //PROJECT_SOFT_BODY_SCREEN_VIEW_H
