#ifndef PROJECT_SOFT_BODY_GUIDE_VIEW_H
#define PROJECT_SOFT_BODY_GUIDE_VIEW_H

#include <string>

#include <vector>

namespace ifx {

struct SoftBodyObjects;

class SoftBodyGuideView {
public:
    SoftBodyGuideView() = default;
    ~SoftBodyGuideView() = default;

    void Render(const SoftBodyObjects &soft_body_objects);
private:
    void RenderSelectorInfo(const SoftBodyObjects &soft_body_objects);
    void RenderScreenInfo();
    void RenderMeshingInfo();
    void RenderMaterialInfo();
    void RenderBoundaryConditionsInfo();
    void RenderLoadInfo();
    void RenderRenderingInfo();
    void RenderSolverInfo();

    void RenderParagraphText(std::string paragraph_name,
                             const std::vector<std::string> &text);
    void RenderParagraphText(std::string text);

};

}

#endif //PROJECT_SOFT_BODY_GUIDE_VIEW_H
