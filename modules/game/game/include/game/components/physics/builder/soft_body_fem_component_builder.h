#ifndef PROJECT_SOFT_BODY_FEM_COMPONENT_BUILDER_H
#define PROJECT_SOFT_BODY_FEM_COMPONENT_BUILDER_H

#include <RTFEM/FEM/FEMGeometry.h>
#include <RTFEM/FEM/Material.h>
#include <RTFEM/FEM/BoundaryConditionContainer.h>
#include <RTFEM/FEM/FEMModel.h>

namespace ifx {

template<class T>
class SoftBodyFEMComponent;

class RenderComponent;

class ResourceManager;

template<class T>
class SoftBodyFEMComponentBuilder {
public:
    SoftBodyFEMComponentBuilder(
            std::shared_ptr<ResourceManager> resource_manager);
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
    void fem_render(std::shared_ptr<RenderComponent> fem_render){
        fem_render_ = fem_render;
    }

    std::shared_ptr<SoftBodyFEMComponent<T>> last_soft_body_fem_component(){
        return last_soft_body_fem_component_;
    }

    std::shared_ptr<SoftBodyFEMComponent<T>> Build();

    rtfem::FEMGeometry<T>& GetFEMGeometry();
    rtfem::Material<T>& GetMaterial();
    rtfem::BoundaryConditionContainer<T>& GetBoundaryConditions();
    Eigen::Vector3<T>& GetBodyForce();

private:
    std::unique_ptr<rtfem::FEMModel<T>> BuildFEMModel();

    std::shared_ptr<SoftBodyFEMComponent<T>> last_soft_body_fem_component_;

    std::shared_ptr<ResourceManager> resource_manager_;

    //

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
