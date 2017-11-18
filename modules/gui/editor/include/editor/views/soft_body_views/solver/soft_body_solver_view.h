#ifndef PROJECT_SOFT_BODY_SOLVER_VIEW_H
#define PROJECT_SOFT_BODY_SOLVER_VIEW_H

#include <memory>
#include <vector>

#include <RTFEM/FEM/Solver/FEMSolverTypes.h>

namespace ifx {

struct SoftBodyEditorObjects;
struct SoftBodyRenderingEffects;

class SceneContainer;
class PhysicsSimulation;

class SoftBodyDynamicSolverView;

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
    SoftBodySolverView(std::shared_ptr<SceneContainer> scene_container,
                       std::shared_ptr<PhysicsSimulation> physics_simulation);
    ~SoftBodySolverView() = default;

    void Render(SoftBodyEditorObjects& soft_body_objects,
                SoftBodyRenderingEffects &rendering_effects);

private:
    void RenderSolverType();

    void RenderStatic(SoftBodyEditorObjects& soft_body_objects);

    rtfem::AnalysisSolverType solver_type_;

    SoftBodySolvers soft_body_solvers_;

    std::unique_ptr<SoftBodyDynamicSolverView> dynamic_solver_view_;

    std::shared_ptr<PhysicsSimulation> physics_simulation_;
};

}

#endif //PROJECT_SOFT_BODY_SOLVER_VIEW_H
