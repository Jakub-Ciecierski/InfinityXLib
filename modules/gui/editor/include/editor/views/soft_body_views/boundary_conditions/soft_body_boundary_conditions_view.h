#ifndef PROJECT_SOFT_BODY_BOUNDARY_CONDITIONS_VIEW_H
#define PROJECT_SOFT_BODY_BOUNDARY_CONDITIONS_VIEW_H

#include <memory>

#include <RTFEM/FEM/FEMModel.h>
#include <RTFEM/FEM/BoundaryCondition.h>

namespace ifx {

struct SoftBodyEditorObjects;
class SoftBodyPicker;

class SoftBodyBoundaryConditionsView {
public:
    SoftBodyBoundaryConditionsView(std::shared_ptr<SoftBodyPicker> picker);
    ~SoftBodyBoundaryConditionsView() = default;

    void Render(
        rtfem::BoundaryConditionContainer<double>& boundary_conditions,
        rtfem::FEMGeometry<double>& fem_geometry);

    void ResetSelectedBoundaryCondition();
private:
    bool StaticCorrectnessAndThrowException(
        const SoftBodyEditorObjects& soft_body_objects);
    bool CheckDynamicCorrectness(
        const SoftBodyEditorObjects& soft_body_objects);

    void RenderCurrentBoundaryConditionsContextMenu(
        rtfem::BoundaryConditionContainer<double>& boundary_conditions);
    void RenderCurrentBoundaryConditions(
        rtfem::BoundaryConditionContainer<double>& boundary_conditions);

    bool RenderSelectedBoundaryConditionsContextMenu(
        const rtfem::BoundaryCondition<double>& boundary_condition,
        int id);
    void RenderSelectedBoundaryCondition();

    void RenderNewBoundaryConditions(
        rtfem::BoundaryConditionContainer<double>& boundary_conditions,
        rtfem::FEMGeometry<double>& fem_geometry);

    std::shared_ptr<SoftBodyPicker> picker_;

    const rtfem::BoundaryCondition<double>* selected_boundary_condition_;
};

}

#endif //PROJECT_SOFT_BODY_BOUNDARY_CONDITIONS_VIEW_H
