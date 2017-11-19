#include "physics/soft_body/soft_body_collisions/soft_body_collider_data.h"

#include <iostream>
#include <math/print_math.h>

namespace ifx {

template<class T>
SoftBodyColliderData<T>::SoftBodyColliderData(
    rtfem::FEMModel<T>* fem_model,
    unsigned int vertex_id) :
    fem_model_(fem_model),
    vertex_id_(vertex_id){}

template<class T>
void SoftBodyColliderData<T>::HandleCollision(
    const glm::vec3& impulse_normal, T impulse_magnitude){
    constexpr float impulse_magnitude_multiplier = 25.0f;
    impulse_magnitude *= impulse_magnitude_multiplier;

    // TODO Efficient way to find triangles by vertex_id
    std::vector<rtfem::TriangleFace<T>*> this_triangle_faces;
    auto& triangle_faces = fem_model_->fem_geometry().triangle_faces;
    for(auto& triangle_face : triangle_faces){
        if(triangle_face.v1 == vertex_id_ ||
            triangle_face.v2 == vertex_id_ ||
            triangle_face.v3 == vertex_id_){
            this_triangle_faces.push_back(&triangle_face);
        }
    }

    for(auto& triangle_face : this_triangle_faces){

        auto triangle_normal = glm::vec3(triangle_face->normal(0),
                                         triangle_face->normal(1),
                                         triangle_face->normal(2));



        float abs_dot = glm::abs(glm::dot(impulse_normal, triangle_normal));
        if(std::isnan(abs_dot)){
            abs_dot = 0;
            std::cout << "nan: abs_dot" << std::endl;
        }

        std::cout << "triangle_normal: " << std::endl;
        ifx::PrintVec3(triangle_normal);
        std::cout << "impulse_normal: " << std::endl;
        ifx::PrintVec3(impulse_normal);
        std::cout << "abs_dot: " << abs_dot << std::endl;
        std::cout << std::endl;

        triangle_face->traction_force = abs_dot * impulse_magnitude;
    }
}

template
class SoftBodyColliderData<double>;
template
class SoftBodyColliderData<float>;

}