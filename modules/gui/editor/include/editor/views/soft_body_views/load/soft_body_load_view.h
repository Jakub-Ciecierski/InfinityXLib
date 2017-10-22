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

    void Render(Eigen::Vector3<double>& body_force);
private:
    void RenderBodyForce(Eigen::Vector3<double>& body_force);

    void RenderTractionForce();
    void RenderTractionForceIsRecording();
    void RenderTractionForceCurrent();

    std::shared_ptr<RenderComponent> traction_force_;
    std::shared_ptr<SoftBodyPicker> soft_body_picker_;

    bool is_recording_traction_force_;
    std::unique_ptr<TractionForceRecorder> traction_force_recorder_;
};

}

#endif //PROJECT_SOFT_BODY_LOAD_VIEW_H
