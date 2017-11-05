#ifndef PROJECT_SOFT_BODY_FEM_SIMULATION_H
#define PROJECT_SOFT_BODY_FEM_SIMULATION_H

#include <memory>
#include <vector>
#include <RTFEM/FEM/Solver/FEMSolvers/FEMDynamicSolver.h>
#include <common/updatable.h>

namespace ifx {

template <class T>
class SoftBodyFEM;

template <class T>
class SoftBodyFEMSimulation : public Updatable {
public:
    SoftBodyFEMSimulation() = default;
    ~SoftBodyFEMSimulation() = default;

    virtual void Update(float delta_time) override;

    void Add(std::shared_ptr<SoftBodyFEM<T>> soft_body);
    bool Remove(std::shared_ptr<SoftBodyFEM<T>> soft_body);

private:

    std::vector<std::shared_ptr<SoftBodyFEM<T>>> soft_bodies_;
    std::vector<std::unique_ptr<rtfem::FEMDynamicSolver<T>>> fem_solvers_;

};

}

#endif //PROJECT_SOFT_BODY_FEM_SIMULATION_H
