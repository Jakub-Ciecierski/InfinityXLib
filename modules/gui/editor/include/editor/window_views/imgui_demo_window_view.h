#ifndef PROJECT_IMGUI_DEMO_VIEW_H
#define PROJECT_IMGUI_DEMO_VIEW_H

#include <editor/window_view.h>

namespace ifx {

class ImGuiDemoWindowView : public WindowView{
public:
    ImGuiDemoWindowView();
    ~ImGuiDemoWindowView();

    virtual void Render() override;

protected:
    virtual void RenderContent() override;

private:
};
}

#endif //PROJECT_IMGUI_DEMO_VIEW_H
