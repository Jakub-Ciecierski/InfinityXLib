#include "physics/soft_body/soft_body_fem.h"

#include <RTFEM/FEM/FEMGeometry.h>

namespace ifx {

template <class T>
SoftBodyFEM<T>::SoftBodyFEM(std::unique_ptr<rtfem::FEMModel<T>> fem_model) :
    fem_model_(std::move(fem_model)){}

template
class SoftBodyFEM<double>;
template
class SoftBodyFEM<float>;

}