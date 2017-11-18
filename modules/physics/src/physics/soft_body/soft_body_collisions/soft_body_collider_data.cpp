#include "physics/soft_body/soft_body_collisions/soft_body_collider_data.h"

namespace ifx {

template<class T>
SoftBodyColliderData<T>::SoftBodyColliderData(
    rtfem::FEMModel<T>* fem_model,
    unsigned int vertex_id) :
    fem_model_(fem_model),
    vertex_id_(vertex_id){}

template
class SoftBodyColliderData<double>;
template
class SoftBodyColliderData<float>;

}