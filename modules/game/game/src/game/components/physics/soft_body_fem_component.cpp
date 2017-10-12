#include "game/components/physics/soft_body_fem_component.h"

#include <RTFEM/FEM/FEMGeometry.h>

namespace ifx {

template<class T>
SoftBodyFEMComponent<T>::SoftBodyFEMComponent(
    std::unique_ptr<rtfem::FEMModel<T>> fem_model) :
    GameComponent(GameComponentType::PHYSICS),
    SoftBodyFEM<T>(std::move(fem_model)){}

template
class SoftBodyFEMComponent<double>;
template
class SoftBodyFEMComponent<float>;

}