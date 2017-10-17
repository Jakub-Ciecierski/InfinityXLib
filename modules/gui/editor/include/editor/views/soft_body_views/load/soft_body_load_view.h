#ifndef PROJECT_SOFT_BODY_LOAD_VIEW_H
#define PROJECT_SOFT_BODY_LOAD_VIEW_H

#include <RTFEM/FEM/FEMModel.h>

namespace ifx {

struct SoftBodyEditorObjects;

class SoftBodyLoadView {
public:
    SoftBodyLoadView() = default;
    ~SoftBodyLoadView() = default;

    void Render(Eigen::Vector3<double>& body_force);
private:
    void RenderBodyForce(Eigen::Vector3<double>& body_force);

};

}

#endif //PROJECT_SOFT_BODY_LOAD_VIEW_H
