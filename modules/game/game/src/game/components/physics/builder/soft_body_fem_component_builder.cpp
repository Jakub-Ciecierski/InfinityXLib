#include "game/components/physics/builder/soft_body_fem_component_builder.h"

#include <game/components/physics/soft_body_fem_component.h>
#include <game/components/physics/builder/meshing_builder.h>

#include <common/unique_ptr.h>

#include <RTFEM/FEM/BoundaryCondition.h>
#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/Vertex.h>

#include <physics/physics_simulation.h>
#include <physics/rigid_body/rigid_body.h>
#include <physics/collision/shapes/sphere_collision_shape.h>
#include "physics/soft_body/soft_body_collisions/soft_body_collider.h"

namespace ifx {

template<class T>
SoftBodyFEMComponentBuilder<T>::SoftBodyFEMComponentBuilder(
    std::shared_ptr<ResourceManager> resource_manager) :
    last_soft_body_fem_component_(nullptr),
    resource_manager_(resource_manager),
    material_(rtfem::Material<T>{80000, 0.3, 1}),
    body_force_(Eigen::Vector3<T>(0, 0, 0)),
    triangle_mesh_render_(nullptr),
    fem_render_(nullptr) {}

template<class T>
std::shared_ptr<SoftBodyFEMComponent<T>>
SoftBodyFEMComponentBuilder<T>::Build(
    std::shared_ptr<PhysicsSimulation> physics_simulation){
    auto fem_model = BuildFEMModel();
    auto colliders = BuildColliders(*fem_model, physics_simulation);
    fem_render_ = BuildRenderComponent(fem_model->fem_geometry(),
                                       resource_manager_);

    auto soft_body_fem_component = std::make_shared<SoftBodyFEMComponent<T>>(
        std::move(fem_model),
        colliders,
        fem_render_);

    last_soft_body_fem_component_ = soft_body_fem_component;

    return soft_body_fem_component;
}

template<class T>
std::unique_ptr<rtfem::FEMModel<T>>
SoftBodyFEMComponentBuilder<T>::BuildFEMModel(){
    auto fem_model = ifx::make_unique<rtfem::FEMModel<T>>(fem_geometry_);
    fem_model->material(material_);
    fem_model->SetStaticBodyForce(body_force_);
    fem_model->boundary_conditions(boundary_conditions_);

    return fem_model;
}

template<class T>
std::vector<std::shared_ptr<SoftBodyCollider<T>>>
SoftBodyFEMComponentBuilder<T>::BuildColliders(
    rtfem::FEMModel<T> &fem_model,
    std::shared_ptr<PhysicsSimulation> physics_simulation){
    std::vector<std::shared_ptr<SoftBodyCollider<T>>> colliders;

    const auto& vertices = fem_model.fem_geometry().vertices;
    auto vertex_count = fem_model.fem_geometry().vertices.size();
    for(unsigned int i = 0; i < vertex_count; i++){
        auto rigid_body = std::make_shared<RigidBody>(
            std::move(physics_simulation->CreateRigidBodyImpl()),
            RigidBodyParams{
                std::make_shared<SphereCollisionShape>(0.1f),
                1.0f
            }
        );
        SoftBodyColliderData<T> collider_data{
            &fem_model,
            vertices[i]->id()
        };
        auto soft_body_collider = std::make_shared<SoftBodyCollider<T>>(
            rigid_body,
            collider_data
        );
    }

    return colliders;
}

template<class T>
std::shared_ptr<RenderComponent>
SoftBodyFEMComponentBuilder<T>::BuildRenderComponent(
    const rtfem::FEMGeometry<T> &fem_geometry,
    std::shared_ptr<ResourceManager> resource_manager){
    return MeshingBuilder<T>().CreateRenderComponent(
        fem_geometry, resource_manager);
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

template
class SoftBodyFEMComponentBuilder<double>;
template
class SoftBodyFEMComponentBuilder<float>;

}