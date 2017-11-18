#include "physics/soft_body/soft_body_fem.h"

#include <physics/soft_body/soft_body_collisions/soft_body_collider.h>
#include <physics/rigid_body/rigid_body.h>

#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>
#include <RTFEM/FEM/BoundaryCondition.h>
#include <RTFEM/FEM/Vertex.h>

namespace ifx {

template <class T>
SoftBodyFEM<T>::SoftBodyFEM(
    std::unique_ptr<rtfem::FEMModel<T>> fem_model,
    const std::vector<std::shared_ptr<SoftBodyCollider<T>>>& colliders) :
    fem_solver_output_(nullptr),
    last_fem_solver_output_(nullptr),
    fem_model_(std::move(fem_model)),
    colliders_(colliders){
    UpdateColliders();
}

template <class T>
void SoftBodyFEM<T>::Update(float time_delta){
    Transformable::Update(time_delta);

    UpdateColliders();
}

template <class T>
void SoftBodyFEM<T>::UpdateColliders(){
    int i = 0;
    for(auto& collider : colliders_){
        auto& vertex = fem_model_->fem_geometry().vertices[i];
        const auto& eigen_coordinates = vertex->coordinates();
        glm::vec3 coordinates{
            eigen_coordinates(0),
            eigen_coordinates(1),
            eigen_coordinates(2)
        };

        glm::vec3 displacement{0, 0, 0};
        if(fem_solver_output_){
            constexpr int dimensions = 3;
            displacement = glm::vec3{
                fem_solver_output_->displacement[i * dimensions + 0],
                fem_solver_output_->displacement[i * dimensions + 1],
                fem_solver_output_->displacement[i * dimensions + 2]
            };
        }

        collider->collider()->SetGlobalTransform(
            coordinates + displacement, glm::quat());
    }
}

template
class SoftBodyFEM<double>;
template
class SoftBodyFEM<float>;

}