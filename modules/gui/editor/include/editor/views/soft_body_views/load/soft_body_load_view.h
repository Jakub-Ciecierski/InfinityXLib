#ifndef PROJECT_SOFT_BODY_LOAD_VIEW_H
#define PROJECT_SOFT_BODY_LOAD_VIEW_H

#include <RTFEM/FEM/FEMModel.h>

namespace ifx {

struct SoftBodyEditorObjects;

class SoftBodyLoadView {
public:
    SoftBodyLoadView() = default;
    ~SoftBodyLoadView() = default;

    void Render(SoftBodyEditorObjects& soft_body_objects);
private:
    bool CheckCorrectness(SoftBodyEditorObjects& soft_body_objects);
    void RenderBodyForce(rtfem::FEMModel<double>& fem_model);

};

}

#endif //PROJECT_SOFT_BODY_LOAD_VIEW_H
