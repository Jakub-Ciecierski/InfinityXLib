#ifndef PROJECT_MESHING_BUILDER_H
#define PROJECT_MESHING_BUILDER_H

#include <RTFEM/FEM/Meshing/TriangleMesh.h>
#include <RTFEM/FEM/FEMGeometry.h>

#include <memory>

namespace ifx {

class RenderComponent;
class ResourceManager;

template <class T>
class MeshingBuilder {
public:
    MeshingBuilder() = default;
    ~MeshingBuilder() = default;

    rtfem::TriangleMeshIndexed<T> CreateTriangleMesh(
        std::shared_ptr<RenderComponent> render_component);

    std::shared_ptr<RenderComponent> CreateRenderComponent(
        const rtfem::FEMGeometry<T> &fem_geometry,
        std::shared_ptr<ResourceManager> resource_manager);

private:
};

}

#endif //PROJECT_MESHING_BUILDER_H
