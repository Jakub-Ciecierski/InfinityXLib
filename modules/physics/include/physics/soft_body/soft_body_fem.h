#ifndef PROJECT_SOFT_BODY_FEM_H
#define PROJECT_SOFT_BODY_FEM_H

#include "RTFEM/FEM/FEMModel.h"

#include <math/transform.h>

namespace ifx {

template<class T>
class SoftBodyFEM : public Transformable {
public:
    SoftBodyFEM(std::unique_ptr<rtfem::FEMModel<T>> fem_model);
    ~SoftBodyFEM() = default;

    rtfem::FEMModel<T>& fem_model(){return *fem_model_;}

private:
    std::unique_ptr<rtfem::FEMModel<T>> fem_model_;
};

}

#endif //PROJECT_SOFT_BODY_FEM_H
