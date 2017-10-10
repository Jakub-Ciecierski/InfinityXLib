#ifndef PROJECT_SOFT_BODY_MESHING_CREATION_VIEW_H
#define PROJECT_SOFT_BODY_MESHING_CREATION_VIEW_H

#include <memory>

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>
#include <RTFEM/FEM/Meshing/TriangleMesh.h>
#include <RTFEM/FEM/FEMGeometry.h>

namespace ifx {

struct SoftBodyObjects;
struct SoftBodyRenderingEffects;

class ResourceManager;
class RenderComponent;

class SoftBodyMeshingCreationView {
public:
    SoftBodyMeshingCreationView(
        std::shared_ptr<ResourceManager> resource_manager);
    ~SoftBodyMeshingCreationView() = default;

    bool Render(const rtfem::TetrahedralizationOptions &rtfem_options,
                SoftBodyObjects &soft_body_objects,
                SoftBodyRenderingEffects &rendering_effects);

private:
    bool BuildMesh(const rtfem::TetrahedralizationOptions &rtfem_options,
                   SoftBodyObjects &soft_body_objects,
                   SoftBodyRenderingEffects &rendering_effects);

    rtfem::TriangleMeshIndexed<double> CreateTriangleMesh(
        SoftBodyObjects &soft_body_objects);
    rtfem::FEMGeometry<double> CreateFEMGeometry(
        const rtfem::TetrahedralizationOptions &rtfem_options,
        const rtfem::TriangleMeshIndexed<double> &triangle_mesh);
    std::shared_ptr<RenderComponent> CreateRenderComponent(
        const rtfem::FEMGeometry<double> &fem_geometry);

    void RegisterRenderComponent(
        std::shared_ptr<RenderComponent> render_component,
        SoftBodyObjects &soft_body_objects,
        SoftBodyRenderingEffects &rendering_effects);

    bool DebugCreator(const rtfem::TetrahedralizationOptions &rtfem_options,
                      SoftBodyObjects &soft_body_objects,
                      SoftBodyRenderingEffects &rendering_effects);

    std::shared_ptr<ResourceManager> resource_manager_;
};

}

#endif //PROJECT_SOFT_BODY_MESHING_CREATION_VIEW_H
