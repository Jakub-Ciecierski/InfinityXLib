#ifndef PROJECT_SOFT_BODY_SOLVER_VIEW_H
#define PROJECT_SOFT_BODY_SOLVER_VIEW_H

#include <RTFEM/FEM/Solver/FEMSolverTypes.h>
#include <RTFEM/FEM/Solver/FEMSolvers/FEMDynamicSolver.h>

namespace ifx {

struct SoftBodyEditorObjects;

template<class T>
class SoftBodyFEMComponent;

class SceneContainer;

struct SoftBodySolvers{
    unsigned int selected = 0;

    const std::string dynamic_name = "Dynamic";
    static constexpr unsigned int dynamic_id = 0;

    const std::string static_name = "Static";
    static constexpr unsigned int static_id = 1;

    const std::vector<std::string> names{
            dynamic_name,
            static_name
    };

};

class SoftBodySolverView {
public:
    SoftBodySolverView(std::shared_ptr<SceneContainer> scene_container);
    ~SoftBodySolverView() = default;

    void Render(SoftBodyEditorObjects& soft_body_objects);

private:
    void RenderSolverType();

    void RenderDynamic(SoftBodyEditorObjects& soft_body_objects);
    void RenderStatic(SoftBodyEditorObjects& soft_body_objects);

    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body_fem_component_;

    rtfem::AnalysisSolverType solver_type_;

    std::unique_ptr<rtfem::FEMDynamicSolver<double>> fem_dynamic_solver_;

    std::shared_ptr<SceneContainer> scene_container_;

    SoftBodySolvers soft_body_solvers_;
};

}

#endif //PROJECT_SOFT_BODY_SOLVER_VIEW_H
