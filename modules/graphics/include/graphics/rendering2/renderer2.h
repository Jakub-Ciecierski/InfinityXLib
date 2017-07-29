#ifndef PROJECT_RENDERER2_H
#define PROJECT_RENDERER2_H

namespace ifx {

struct RenderingState;

class Renderer2 {
public:

    Renderer2();

    ~Renderer2();

    void SetState(const RenderingState& rendering_state);
private:
};
}


#endif //PROJECT_RENDERER2_H
