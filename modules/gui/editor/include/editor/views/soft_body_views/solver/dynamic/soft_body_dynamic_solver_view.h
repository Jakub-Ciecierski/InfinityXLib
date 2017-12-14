#ifndef PROJECT_SOFT_BODY_DYNAMIC_SOLVER_VIEW_H
#define PROJECT_SOFT_BODY_DYNAMIC_SOLVER_VIEW_H

#include <memory>
#include <string>
#include <vector>

namespace ifx {

class SceneContainer;
class PhysicsSimulation;
class Updatable;

struct SoftBodyEditorObjects;
struct SoftBodyRenderingEffects;

template<class T>
class SoftBodyFEMComponent;

class GameObject;

struct TimeRestriction {
    bool do_time_restriction = false;
    float time_seconds = 2.0f;
};

struct SoftBodyLinearSolvers{
    unsigned int selected = 0;

    const std::string cg_name = "CG";
    static constexpr unsigned int cg_id = 0;

    const std::string cg_precond_name = "CG PreCond";
    static constexpr unsigned int cg_precond_id = 1;

    const std::string lu_name = "LU";
    static constexpr unsigned int lu_id = 2;

    const std::vector<std::string> names{
            cg_name,
            cg_precond_name,
            lu_name
    };

};

class SoftBodyDynamicSolverView {
public:
    SoftBodyDynamicSolverView(std::shared_ptr<SceneContainer> scene_container,
                              std::shared_ptr<PhysicsSimulation> physics_simulation);

    ~SoftBodyDynamicSolverView() = default;

    void Render(SoftBodyEditorObjects& soft_body_objects,
                SoftBodyRenderingEffects &rendering_effects);
private:
    void HandleTimeRestrictions();

    void RenderBuild(SoftBodyEditorObjects& soft_body_objects,
                     SoftBodyRenderingEffects &rendering_effects);

    void RenderPlayPauseSolver();
    void RenderStepSolver();
    void RenderResetSolver();

    void RenderSolverSettings();
    void RenderSetTimeStep();
    void RenderSetTimeStepPhysics();
    void RenderSetTimeStepRenderingSynchronization();
    void RenderUpdateSettings(
            std::shared_ptr<Updatable> updatable,
            std::string name);
    void RenderSolverType();

    void RenderSetTimeRestrictions();

    void RenderSimulationInformation();
    void RenderComputationTimers();
    void RenderComputationTimer(const std::string &name,
                                double total_time,
                                double time);
    void Play();
    void Pause();
    void StepSolver();

    std::shared_ptr<SceneContainer> scene_container_;
    std::shared_ptr<PhysicsSimulation> physics_simulation_;

    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body_fem_component_;
    std::shared_ptr<GameObject> soft_body_fem_game_object_;

    TimeRestriction time_restriction_;

    SoftBodyLinearSolvers linear_solvers_;
};
}


#endif //PROJECT_SOFT_BODY_DYNAMIC_SOLVER_VIEW_H
