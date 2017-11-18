#ifndef PROJECT_SOFT_BODY_FEM_H
#define PROJECT_SOFT_BODY_FEM_H

#include "RTFEM/FEM/FEMModel.h"
#include <RTFEM/FEM/Solver/FEMSolver.h>

#include <math/transform.h>

namespace ifx {

template<class T>
class SoftBodyCollider;

/**
 * Contains kinematic rigid bodies acting as colliders for each FEM vertex.
 * @tparam T
 */
template<class T>
class SoftBodyFEM : public Transformable {
public:
    SoftBodyFEM(
        std::unique_ptr<rtfem::FEMModel<T>> fem_model,
        const std::vector<std::shared_ptr<SoftBodyCollider<T>>>& colliders);
    ~SoftBodyFEM() = default;

    rtfem::FEMModel<T>* fem_model(){return fem_model_.get();}

    const rtfem::FEMSolverOutput<T>* last_fem_solver_output(){
        return last_fem_solver_output_;
    };
    void fem_solver_output(const rtfem::FEMSolverOutput<T>* fem_solver_output){
        fem_solver_output_ = fem_solver_output;
    }

    const std::vector<std::shared_ptr<SoftBodyCollider<T>>>& colliders() const {
        return colliders_;
    }

    virtual void Update(float time_delta) override;
protected:
    void UpdateColliders();

    const rtfem::FEMSolverOutput<T>* fem_solver_output_;
    const rtfem::FEMSolverOutput<T>* last_fem_solver_output_;

    std::unique_ptr<rtfem::FEMModel<T>> fem_model_;

    std::vector<std::shared_ptr<SoftBodyCollider<T>>> colliders_;
};

}

#endif //PROJECT_SOFT_BODY_FEM_H
