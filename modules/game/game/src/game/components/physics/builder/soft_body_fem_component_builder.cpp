#include "game/components/physics/builder/soft_body_fem_component_builder.h"

#include <game/components/physics/soft_body_fem_component.h>

#include <common/unique_ptr.h>

#include <RTFEM/FEM/FEMModel.h>
#include <RTFEM/FEM/BoundaryCondition.h>

namespace ifx {

template<class T>
SoftBodyFEMComponentBuilder<T>::SoftBodyFEMComponentBuilder() :
    material_(rtfem::Material<T>{80000, 0.3, 1}),
    body_force_(Eigen::Vector3<T>(0,0,0)),
    triangle_mesh_render_(nullptr),
    fem_render_(nullptr) {}

template<class T>
std::shared_ptr<SoftBodyFEMComponent<T>>
SoftBodyFEMComponentBuilder<T>::Build(){
    auto fem_model = ifx::make_unique<rtfem::FEMModel<T>>(
        fem_geometry_, std::move(material_));
    fem_model->SetBodyForce(body_force_);
    fem_model->boundary_conditions(boundary_conditions_);

    auto soft_body_fem_component = std::make_shared<SoftBodyFEMComponent<T>>(
        std::move(fem_model));

    return soft_body_fem_component;
}

template<class T>
rtfem::FEMGeometry<T>& SoftBodyFEMComponentBuilder<T>::GetFEMGeometry(){
    return fem_geometry_;
}

template<class T>
rtfem::Material<T>& SoftBodyFEMComponentBuilder<T>::GetMaterial(){
    return material_;
}

template<class T>
rtfem::BoundaryConditionContainer<T>&
SoftBodyFEMComponentBuilder<T>::GetBoundaryConditions(){
    return boundary_conditions_;
}

template<class T>
Eigen::Vector3<T>& SoftBodyFEMComponentBuilder<T>::GetBodyForce(){
    return body_force_;
}

template<class T>
SoftBodyFEMComponentBuilder<T>& SoftBodyFEMComponentBuilder<T>::SetFEMGeometry(
    const rtfem::FEMGeometry<T>& fem_geometry){

}

template<class T>
SoftBodyFEMComponentBuilder<T>& SoftBodyFEMComponentBuilder<T>::SetMaterial(
    const rtfem::Material<T>& material){

}

template<class T>
SoftBodyFEMComponentBuilder<T>&
SoftBodyFEMComponentBuilder<T>::SetBoundaryConditions(
    const rtfem::BoundaryConditionContainer<T>& boundary_conditions){


}

template<class T>
SoftBodyFEMComponentBuilder<T>& SoftBodyFEMComponentBuilder<T>::SetBodyForce(
    const Eigen::Vector3<T>& body_force){

}

template
class SoftBodyFEMComponentBuilder<double>;
template
class SoftBodyFEMComponentBuilder<float>;

}