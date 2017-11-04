#include "game/components/physics/soft_body_fem_component.h"

#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>
#include <RTFEM/FEM/BoundaryCondition.h>

namespace ifx {

template<class T>
SoftBodyFEMComponent<T>::SoftBodyFEMComponent(
    std::unique_ptr<rtfem::FEMModel<T>> fem_model,
    std::shared_ptr<RenderComponent> render_component) :
    GameComponent(GameComponentType::PHYSICS),
    SoftBodyFEM<T>(std::move(fem_model)),
    render_component_(render_component){}

template
class SoftBodyFEMComponent<double>;
template
class SoftBodyFEMComponent<float>;

}