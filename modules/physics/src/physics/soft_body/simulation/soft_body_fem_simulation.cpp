#include "physics/soft_body/simulation/soft_body_fem_simulation.h"

#include <physics/soft_body/soft_body_fem.h>

#include <common/unique_ptr.h>

#include "RTFEM/GPU/LinearSolver/GPULULinearSolver.cuh"

namespace ifx {

template <class T>
SoftBodyFEMSimulation<T>::SoftBodyFEMSimulation() :
        fem_solver_type_(rtfem::FEMSolverType::GPU),
        linear_system_solver_type_(rtfem::LinearSystemSolverType::CG){}

template <class T>
void SoftBodyFEMSimulation<T>::Update(float delta_time){
    int i = 0;
    for(auto& fem_solver : fem_solvers_){
        fem_solver->RunIteration();

        auto& soft_body_fem = soft_bodies_[i];
        soft_body_fem->fem_solver_output(fem_solver->solver_output());
        i++;
    }
}

template<class T>
void SoftBodyFEMSimulation<T>::Add(std::shared_ptr<SoftBodyFEM<T>> soft_body,
                                   T time_delta) {
    soft_bodies_.push_back(soft_body);

    auto fem_solver = ifx::make_unique<rtfem::FEMDynamicSolver<T>>(
            soft_body->fem_model(),
            linear_system_solver_type_,
            time_delta);
    fem_solver->type(fem_solver_type_);
    fem_solver->Solve();
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

template <class T>
void SoftBodyFEMSimulation<T>::SetFEMSolverType(
        const rtfem::FEMSolverType& type){
    fem_solver_type_ = type;
    for(auto& fem_solver : fem_solvers_){
        fem_solver->type(fem_solver_type_);
    }
}

template <class T>
rtfem::FEMSolverType SoftBodyFEMSimulation<T>::GetFEMSolverType(){
    return fem_solver_type_;
}

template <class T>
void SoftBodyFEMSimulation<T>::SetLinearSystemSolverType(
        const rtfem::LinearSystemSolverType& type){
    linear_system_solver_type_ = type;
}

template <class T>
rtfem::LinearSystemSolverType
SoftBodyFEMSimulation<T>::GetLinearSystemSolverType(){
    return linear_system_solver_type_;
}

template class SoftBodyFEMSimulation<double>;
template class SoftBodyFEMSimulation<float>;

}