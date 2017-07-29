#ifndef PROJECT_RENDERING_STATE_H
#define PROJECT_RENDERING_STATE_H

#include <graphics/rendering2/states/blend_state.h>
#include <graphics/rendering2/states/depth_state.h>

namespace ifx {

struct RenderingState {
public:

    RenderingState();

    ~RenderingState();

    BlendState blend_state;
    DepthState depth_state;

private:

};
}


#endif //PROJECT_RENDERING_STATE_H
