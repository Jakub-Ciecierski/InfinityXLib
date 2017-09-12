#ifndef PROJECT_MESH_FACTORY_H
#define PROJECT_MESH_FACTORY_H

#include <graphics/model/mesh.h>

#include <memory>

namespace ifx {

class TextureCreator;

class MeshFactory {
private:

public:

    MeshFactory(std::shared_ptr<TextureCreator> texture_creator);

    ~MeshFactory();

    std::unique_ptr<Mesh> CreateQuad(int x, int y);
    std::unique_ptr<Mesh> CreateLine(const glm::vec3 &p1,
                                     const glm::vec3 &p2);

    std::unique_ptr<Mesh> LoadBicubicBezierPatch(float startX,
                                                 float startY,
                                                 float depth,
                                                 int idI = 0,
                                                 int idJ = 0);
    std::unique_ptr<Mesh> LoadBicubicBezierPolygon(float startX,
                                                   float startY,
                                                   float depth,
                                                   int idI = 0,
                                                   int idJ = 0);
    std::unique_ptr<Mesh> LoadBicubicBezierAsymmetricPatch();

    std::unique_ptr<Mesh> LoadPatch();
    std::unique_ptr<Mesh> LoadCubemap();
    std::unique_ptr<Mesh> LoadCAMMaterial();
    std::unique_ptr<Mesh> LoadCube();
    std::unique_ptr<Mesh> LoadRoom();
    std::unique_ptr<Mesh> LoadFloor();
    std::unique_ptr<Mesh> LoadLamp();

    std::unique_ptr<Mesh> LoadCubeUnTextured();
    std::unique_ptr<Mesh> LoadHalfSphere(float radius = 2);
    std::unique_ptr<Mesh> LoadSphere(float radius = 2);
    std::unique_ptr<Mesh> LoadCircle(float radius = 2);

private:
    std::shared_ptr<TextureCreator> texture_creator_;
};
}

#endif //PROJECT_MESH_FACTORY_H
