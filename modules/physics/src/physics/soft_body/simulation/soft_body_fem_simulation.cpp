#include "physics/soft_body/simulation/soft_body_fem_simulation.h"

#include <physics/soft_body/soft_body_fem.h>

#include <common/unique_ptr.h>

namespace ifx {

template <class T>
void SoftBodyFEMSimulation<T>::Update(float delta_time){
    for(auto& fem_solver : fem_solvers_){
        fem_solver->RunIteration();
    }
}

template <class T>
void SoftBodyFEMSimulation<T>::Add(std::shared_ptr<SoftBodyFEM<T>> soft_body){
    soft_bodies_.push_back(soft_body);

    T delta_time = 1.0 / 60.0;
    auto fem_solver = ifx::make_unique<rtfem::FEMDynamicSolver<T>>(delta_time);
    fem_solver->Solve(soft_body->fem_model());
    fem_solvers_.push_back(std::move(fem_solver));
}

template <class T>
bool SoftBodyFEMSimulation<T>::Remove(
    std::shared_ptr<SoftBodyFEM<T>> soft_body){
    for (unsigned int i = 0; i < soft_bodies_.size(); i++) {
        if (soft_bodies_[i] == soft_body) {
            soft_bodies_.erase(soft_bodies_.begin() + i);
            fem_solvers_.erase(fem_solvers_.begin() + i);
            return true;
        }
    }
    return false;
}

template class SoftBodyFEMSimulation<double>;
template class SoftBodyFEMSimulation<float>;

}