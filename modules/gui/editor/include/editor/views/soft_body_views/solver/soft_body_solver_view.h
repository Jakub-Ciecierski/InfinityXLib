#ifndef PROJECT_SOFT_BODY_SOLVER_VIEW_H
#define PROJECT_SOFT_BODY_SOLVER_VIEW_H

#include <RTFEM/FEM/Solver/FEMSolverTypes.h>
#include <RTFEM/FEM/Solver/FEMSolvers/FEMDynamicSolver.h>

namespace ifx {

struct SoftBodyEditorObjects;

template<class T>
class SoftBodyFEMComponent;

class SceneContainer;

class SoftBodySolverView {
public:
    SoftBodySolverView(std::shared_ptr<SceneContainer> scene_container);
    ~SoftBodySolverView() = default;

    void Render(SoftBodyEditorObjects& soft_body_objects);

private:
    void RenderDynamic(SoftBodyEditorObjects& soft_body_objects);

    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body_fem_component_;

    rtfem::AnalysisSolverType solver_type_;

    std::unique_ptr<rtfem::FEMDynamicSolver<double>> fem_dynamic_solver_;

    std::shared_ptr<SceneContainer> scene_container_;
};

}

#endif //PROJECT_SOFT_BODY_SOLVER_VIEW_H
