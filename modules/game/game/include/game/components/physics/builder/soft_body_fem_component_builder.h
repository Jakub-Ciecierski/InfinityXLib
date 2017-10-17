#ifndef PROJECT_SOFT_BODY_FEM_COMPONENT_BUILDER_H
#define PROJECT_SOFT_BODY_FEM_COMPONENT_BUILDER_H

#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/Material.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>

namespace ifx {

template<class T>
class SoftBodyFEMComponent;

class RenderComponent;

template<class T>
class SoftBodyFEMComponentBuilder {
public:
    SoftBodyFEMComponentBuilder();
    ~SoftBodyFEMComponentBuilder() = default;

    std::shared_ptr<RenderComponent> triangle_mesh_render(){
        return triangle_mesh_render_;
    }
    void triangle_mesh_render(
        std::shared_ptr<RenderComponent> triangle_mesh_render){
        triangle_mesh_render_ = triangle_mesh_render;
    }

    std::shared_ptr<RenderComponent> fem_render(){
        return fem_render_;
    }
    void fem_render(
        std::shared_ptr<RenderComponent> fem_render){
        fem_render_ = fem_render;
    }

    std::shared_ptr<SoftBodyFEMComponent<T>> Build();

    rtfem::FEMGeometry<T>& GetFEMGeometry();
    rtfem::Material<T>& GetMaterial();
    rtfem::BoundaryConditionContainer<T>& GetBoundaryConditions();
    Eigen::Vector3<T>& GetBodyForce();

    SoftBodyFEMComponentBuilder& SetFEMGeometry(
        const rtfem::FEMGeometry<T>& fem_geometry);
    SoftBodyFEMComponentBuilder& SetMaterial(
        const rtfem::Material<T>& material);
    SoftBodyFEMComponentBuilder& SetBoundaryConditions(
        const rtfem::BoundaryConditionContainer<T>& boundary_conditions);
    SoftBodyFEMComponentBuilder& SetBodyForce(
        const Eigen::Vector3<T>& body_force);
private:

    rtfem::FEMGeometry<T> fem_geometry_;

    rtfem::Material<T> material_;

    rtfem::BoundaryConditionContainer<T> boundary_conditions_;

    Eigen::Vector3<T> body_force_;

    /**
     * Input Triangle Mesh. Take vertices and create FEMGeometry based of it.
     */
    std::shared_ptr<RenderComponent> triangle_mesh_render_;

    /**
     * Output FEM Mesh. The visual counter-part of FEMGeometry
     */
    std::shared_ptr<RenderComponent> fem_render_;
};

}

#endif //PROJECT_SOFT_BODY_FEM_COMPONENT_BUILDER_H