#ifndef PROJECT_SOFT_BODY_DYNAMIC_SOLVER_VIEW_H
#define PROJECT_SOFT_BODY_DYNAMIC_SOLVER_VIEW_H

#include <memory>
#include <string>

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

    void RenderSetTimeRestrictions();

    void RenderSimulationInformation();

    void Play();
    void Pause();
    void StepSolver();

    std::shared_ptr<SceneContainer> scene_container_;
    std::shared_ptr<PhysicsSimulation> physics_simulation_;

    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body_fem_component_;
    std::shared_ptr<GameObject> soft_body_fem_game_object_;

    TimeRestriction time_restriction_;
};
}


#endif //PROJECT_SOFT_BODY_DYNAMIC_SOLVER_VIEW_H
