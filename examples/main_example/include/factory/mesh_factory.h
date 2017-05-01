#ifndef PROJECT_MESH_FACTORY_H
#define PROJECT_MESH_FACTORY_H

#include <graphics/model/mesh.h>

#include <memory>

namespace ifx {

class MeshFactory {
private:

public:

    MeshFactory();

    ~MeshFactory();

    static std::unique_ptr<Mesh> CreateQuad(int x, int y);
    static std::unique_ptr<Mesh> CreateLine(const glm::vec3& p1,
                                            const glm::vec3& p2);

    static std::unique_ptr<Mesh> LoadBicubicBezierPatch(float startX,
                                                        float startY,
                                                        float depth,
                                                        int idI = 0,
                                                        int idJ = 0);
    static std::unique_ptr<Mesh> LoadBicubicBezierPolygon(float startX,
                                                          float startY,
                                                          float depth,
                                                          int idI = 0,
                                                          int idJ = 0);
    static std::unique_ptr<Mesh> LoadBicubicBezierAsymmetricPatch();

    static std::unique_ptr<Mesh> LoadPatch();
    static std::unique_ptr<Mesh> LoadCubemap();
    static std::unique_ptr<Mesh> LoadCAMMaterial();
    static std::unique_ptr<Mesh> LoadCube();
    static std::unique_ptr<Mesh> LoadRoom();
    static std::unique_ptr<Mesh> LoadFloor();
    static std::unique_ptr<Mesh> LoadLamp();

    static std::unique_ptr<Mesh> LoadCubeUnTextured();
    static std::unique_ptr<Mesh> LoadHalfSphere(float radius = 2);
    static std::unique_ptr<Mesh> LoadSphere(float radius = 2);
    static std::unique_ptr<Mesh> LoadCircle(float radius = 2);
};
}

#endif //PROJECT_MESH_FACTORY_H
