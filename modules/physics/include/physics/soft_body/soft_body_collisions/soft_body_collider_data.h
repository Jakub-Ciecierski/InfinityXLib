#ifndef PROJECT_SOFT_BODY_COLLIDER_DATA_H
#define PROJECT_SOFT_BODY_COLLIDER_DATA_H

#include <RTFEM/FEM/FEMModel.h>

#include <math/math_ifx.h>

namespace ifx {

template<class T>
class SoftBodyColliderData {
public:
    SoftBodyColliderData(
        rtfem::FEMModel<T>* fem_model,
        unsigned int vertex_id);

    ~SoftBodyColliderData() = default;

    unsigned int vertex_id() const {return vertex_id_;}

    void HandleCollision(const glm::vec3& impulse_normal, T impulse_magnitude);

private:
    rtfem::FEMModel<T>* fem_model_;
    unsigned int vertex_id_;
};

}

#endif //PROJECT_SOFT_BODY_COLLIDER_DATA_H