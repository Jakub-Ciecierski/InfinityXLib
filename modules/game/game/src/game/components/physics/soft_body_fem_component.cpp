#include "game/components/physics/soft_body_fem_component.h"

#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>
#include <RTFEM/FEM/BoundaryCondition.h>
#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/Vertex.h>

#include <game/components/render/render_component.h>

#include <graphics/model/model.h>

namespace ifx {

template<class T>
SoftBodyFEMComponent<T>::SoftBodyFEMComponent(
    std::unique_ptr<rtfem::FEMModel<T>> fem_model,
    const std::vector<std::shared_ptr<SoftBodyCollider<T>>>& colliders,
    std::shared_ptr<RenderComponent> render_component) :
    GameComponent(GameComponentType::PHYSICS_SOFT_BODY),
    SoftBodyFEM<T>(std::move(fem_model), colliders),
    render_component_(render_component){}

template<class T>
void SoftBodyFEMComponent<T>::Update(float time_delta) {
    SoftBodyFEM<T>::Update(time_delta);

    if(this->fem_solver_output_){
        UpdateVBOPositions();
        // TODO nulling fem_solver_output_ to avoid overhead
        // might not be the best solution
        this->last_fem_solver_output_ = this->fem_solver_output_;
        this->fem_solver_output_ = nullptr;
    }
}

template<class T>
void SoftBodyFEMComponent<T>::UpdateVBOPositions(){
    auto* vbo = render_component_->models()[0]->getMesh(0)->vbo();
    const auto& origin_vertices = this->fem_model_->fem_geometry().vertices;
    const auto& displacements = this->fem_solver_output_->displacement;
    auto* vertices = vbo->vertices();

    for(unsigned int i = 0; i < vertices->size(); i++){
        auto displacement_index_start = i * 3;
        auto displacement_x = displacements[displacement_index_start];
        auto displacement_y = displacements[displacement_index_start + 1];
        auto displacement_z = displacements[displacement_index_start + 2];

        auto& origin_vertex = origin_vertices[i];
        auto& vertex = (*vertices)[i];
        vertex.Position.x = origin_vertex->x() + displacement_x;
        vertex.Position.y = origin_vertex->y() + displacement_y;
        vertex.Position.z = origin_vertex->z() + displacement_z;
    }

    vbo->Update();
}

template
class SoftBodyFEMComponent<double>;
template
class SoftBodyFEMComponent<float>;

}