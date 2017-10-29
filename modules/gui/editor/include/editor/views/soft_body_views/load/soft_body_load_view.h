#ifndef PROJECT_SOFT_BODY_LOAD_VIEW_H
#define PROJECT_SOFT_BODY_LOAD_VIEW_H

#include <RTFEM/FEM/FEMModel.h>

namespace ifx {

class RenderComponent;
struct SoftBodyEditorObjects;
class SoftBodyPicker;
class TractionForceRecorder;

class SoftBodyLoadView {
public:
    SoftBodyLoadView(std::shared_ptr<RenderComponent> traction_force,
                     std::shared_ptr<SoftBodyPicker> soft_body_picker);
    ~SoftBodyLoadView() = default;

    void Render(Eigen::Vector3<double>& body_force,
                std::vector<rtfem::TriangleFace<double>>& triangle_faces);
private:
    void RenderBodyForce(Eigen::Vector3<double>& body_force);

    void RenderTractionForce(
        std::vector<rtfem::TriangleFace<double>>& triangle_faces);

    void RenderTractionForceCurrent(
        std::vector<rtfem::TriangleFace<double>>& triangle_faces);
    void RenderTractionForceInspector(
        std::vector<rtfem::TriangleFace<double>>& triangle_faces);

    void RecordTractionForce(
        std::vector<rtfem::TriangleFace<double>>& triangle_faces);

    bool RenderTractionForceError(
        const std::vector<rtfem::TriangleFace<double>>& triangle_faces);

    std::shared_ptr<RenderComponent> traction_force_;
    std::shared_ptr<SoftBodyPicker> soft_body_picker_;

    std::unique_ptr<TractionForceRecorder> traction_force_recorder_;

    int selected_triangle_face_;
};

}

#endif //PROJECT_SOFT_BODY_LOAD_VIEW_H
