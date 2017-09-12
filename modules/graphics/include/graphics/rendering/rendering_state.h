#ifndef PROJECT_RENDERING_STATE_H
#define PROJECT_RENDERING_STATE_H

#include <graphics/rendering/states/blend_state.h>
#include <graphics/rendering/states/depth_state.h>

namespace ifx {

struct RenderingState {
public:

    RenderingState() = default;
    ~RenderingState() = default;

    BlendState blend_state;
    DepthState depth_state;

    // Higher priority will be rendered first
    unsigned int drawing_priority = 0;

private:

};
}

#endif //PROJECT_RENDERING_STATE_H
