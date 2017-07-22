#ifndef PROJECT_IMGUI_DEMO_VIEW_H
#define PROJECT_IMGUI_DEMO_VIEW_H

#include <editor/view.h>

namespace ifx {

class ImGuiDemoView : public View{
public:
    ImGuiDemoView();
    ~ImGuiDemoView();

    virtual void Render() override;

protected:

    virtual void RenderContent() override;

private:
};
}

#endif //PROJECT_IMGUI_DEMO_VIEW_H
