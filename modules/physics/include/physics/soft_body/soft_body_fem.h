#ifndef PROJECT_SOFT_BODY_FEM_H
#define PROJECT_SOFT_BODY_FEM_H

#include "RTFEM/FEM/FEMModel.h"
#include <RTFEM/FEM/Solver/FEMSolver.h>

#include <math/transform.h>

namespace ifx {

template<class T>
class SoftBodyFEM : public Transformable {
public:
    SoftBodyFEM(std::unique_ptr<rtfem::FEMModel<T>> fem_model);
    ~SoftBodyFEM() = default;

    rtfem::FEMModel<T>& fem_model(){return *fem_model_;}

    void fem_solver_output(const rtfem::FEMSolverOutput<T>* fem_solver_output){
        fem_solver_output_ = fem_solver_output;
    }

protected:
    const rtfem::FEMSolverOutput<T>* fem_solver_output_;

private:
    std::unique_ptr<rtfem::FEMModel<T>> fem_model_;
};

}

#endif //PROJECT_SOFT_BODY_FEM_H
