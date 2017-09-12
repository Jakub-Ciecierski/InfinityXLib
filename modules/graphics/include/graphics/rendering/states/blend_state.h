#ifndef PROJECT_BLEND_STATE_H
#define PROJECT_BLEND_STATE_H

#include <graphics/rendering/states/state.h>

namespace ifx {

enum class BlendFunction {
    SourceAlpha, OneMinusSourceAlpha
};

enum class BlendEquation {
    Addition, Subtract, Min, Max
};

struct BlendState : public State {
    BlendFunction source_factor = BlendFunction::SourceAlpha;
    BlendFunction destination_factor = BlendFunction::SourceAlpha;

    BlendEquation equation = BlendEquation::Addition;
};

}

#endif //PROJECT_BLEND_STATE_H
