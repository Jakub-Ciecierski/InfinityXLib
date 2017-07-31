#ifndef PROJECT_RENDERING_VIEW_H
#define PROJECT_RENDERING_VIEW_H

#include <editor/view.h>

#include <memory>

namespace ifx {

class RenderingEffectProcessor;

class RenderingView : public View {
public:
    RenderingView(
            std::shared_ptr<RenderingEffectProcessor> rendering_effect_processor);
    ~RenderingView() = default;

    virtual void Render() override;
private:
    std::shared_ptr<RenderingEffectProcessor> rendering_effect_processor_;
};
}

#endif //PROJECT_RENDERING_VIEW_H
