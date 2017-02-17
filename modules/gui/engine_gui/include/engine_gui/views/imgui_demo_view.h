#ifndef PROJECT_IMGUI_DEMO_VIEW_H
#define PROJECT_IMGUI_DEMO_VIEW_H

#include <engine_gui/view.h>

namespace ifx {

class ImGuiDemoView : public View{
public:
    ImGuiDemoView();
    ~ImGuiDemoView();

    void Render() override;
private:
};
}

#endif //PROJECT_IMGUI_DEMO_VIEW_H
