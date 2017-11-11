#include "game/components/physics/soft_body_fem_component.h"

#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>
#include <RTFEM/FEM/BoundaryCondition.h>

#include <game/components/render/render_component.h>

#include <graphics/model/model.h>

namespace ifx {

template<class T>
SoftBodyFEMComponent<T>::SoftBodyFEMComponent(
    std::unique_ptr<rtfem::FEMModel<T>> fem_model,
    std::shared_ptr<RenderComponent> render_component) :
    GameComponent(GameComponentType::PHYSICS_SOFT_BODY),
    SoftBodyFEM<T>(std::move(fem_model)),
    render_component_(render_component){}

template<class T>
void SoftBodyFEMComponent<T>::Update(float time_delta) {
    Transformable::Update(time_delta);

    if(this->fem_solver_output_)
        UpdateVBOPositions();
}

template<class T>
void SoftBodyFEMComponent<T>::UpdateVBOPositions(){
    auto* vbo = render_component_->models()[0]->getMesh(0)->vbo();
    auto* vertices = vbo->vertices();
    for(unsigned int i = 0; i < vertices->size(); i++){
        auto& vertex = (*vertices)[i];
        auto displacement_index_start = i * 3;
        auto displacement_x
                = this->fem_solver_output_->displacement[displacement_index_start];
        auto displacement_y
                = this->fem_solver_output_->displacement[displacement_index_start + 1];
        auto displacement_z
                = this->fem_solver_output_->displacement[displacement_index_start + 2];

        vertex.Position.x += displacement_x;
        vertex.Position.y += displacement_y;
        vertex.Position.z += displacement_z;
    }

    vbo->Update();

    this->fem_solver_output_ = nullptr;
}

template
class SoftBodyFEMComponent<double>;
template
class SoftBodyFEMComponent<float>;

}