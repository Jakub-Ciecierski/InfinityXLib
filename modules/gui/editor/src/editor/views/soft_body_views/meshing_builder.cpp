#include "editor/views/soft_body_views/meshing_builder.h"

#include <game/components/render/render_component.h>

#include <graphics/model/model.h>
#include <graphics/model/mesh.h>
#include <graphics/shaders/data/shader_data.h>
#include <graphics/model/model_creator.h>

#include <RTFEM/FEM/Meshing/TriangleMesh.h>
#include <RTFEM/DataTypes.h>
#include <RTFEM/FEM/Vertex.h>

#include <common/unique_ptr.h>

namespace ifx {

rtfem::TriangleMeshIndexed<double> MeshingBuilder::CreateTriangleMesh(
        std::shared_ptr<RenderComponent> render_component){
    rtfem::TriangleMeshIndexed<double> triangle_mesh;

    auto models = render_component->models();
    for(auto& model : models){
        auto meshes = model->getMeshes();
        for(auto& mesh : meshes){
            const auto& vertices = mesh->vertices();
            const auto& indices = mesh->indices();

            unsigned int starting_index = triangle_mesh.points.size();

            for(auto& vertex : vertices){
                auto eigen_vertex = Eigen::Vector3<double>(
                        vertex.Position.x,
                        vertex.Position.y,
                        vertex.Position.z
                );
                triangle_mesh.points.push_back(eigen_vertex);
            }

            constexpr unsigned int TRIANGLE_VERTEX_COUNT = 3;
            for(unsigned int i = 0;
                i < indices.size() / TRIANGLE_VERTEX_COUNT; i++){
                unsigned int v1 = i * TRIANGLE_VERTEX_COUNT + 0;
                unsigned int v2 = i * TRIANGLE_VERTEX_COUNT + 1;
                unsigned int v3 = i * TRIANGLE_VERTEX_COUNT + 2;

                if(v1 >= indices.size()
                   || v2 >= indices.size()
                   || v3 >= indices.size()){
                    throw std::invalid_argument(
                            "CreateTriangleMesh Triangle out of bounds");
                }
                auto triangle = rtfem::TriangleIndices{
                        indices[starting_index + v1],
                        indices[starting_index + v2],
                        indices[starting_index + v3]};
                triangle_mesh.triangles.push_back(triangle);
            }
        }
    }

    return triangle_mesh;
}

std::shared_ptr<RenderComponent> MeshingBuilder::CreateRenderComponent(
        const rtfem::FEMGeometry<double>& fem_geometry,
        std::shared_ptr<ResourceManager> resource_manager){
    unsigned int point_count= fem_geometry.vertices.size();
    unsigned int triangle_count = fem_geometry.finite_element_faces.size();

    std::vector<Vertex> vertices(point_count);
    std::vector<unsigned int> indices(triangle_count*3);

    for(unsigned int i = 0; i < vertices.size(); i++){
        vertices[i].Position.x = fem_geometry.vertices[i]->x();
        vertices[i].Position.y = fem_geometry.vertices[i]->y();
        vertices[i].Position.z = fem_geometry.vertices[i]->z();
    }

    for(unsigned int i = 0; i < triangle_count; i++){
        indices[i*3 + 0] = fem_geometry.finite_element_faces[i].v1;
        indices[i*3 + 1] = fem_geometry.finite_element_faces[i].v2;
        indices[i*3 + 2] = fem_geometry.finite_element_faces[i].v3;
    }

    auto mesh = ifx::make_unique<Mesh>(vertices, indices);
    auto model = ModelCreator(resource_manager).MakeModel(ifx::NO_FILEPATH,
                                                          std::move(mesh));
    return std::make_shared<RenderComponent>(model);
}

}