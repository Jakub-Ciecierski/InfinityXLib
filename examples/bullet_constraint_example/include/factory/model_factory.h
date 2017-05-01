#ifndef PROJECT_MODEL_FACTORY_H
#define PROJECT_MODEL_FACTORY_H

#include <graphics/model/model.h>

#include <memory>

namespace ifx {

class ModelFactory {
public:

    ModelFactory();
    ~ModelFactory();

    static std::shared_ptr<Model> LoadAsteroidModel();
    static std::shared_ptr<Model> LoadNanoSuitModel();

    static std::shared_ptr<Model> CreateQuad(int x, int y);

    static std::shared_ptr<Model> LoadBicubicBezierSurfaceC0();
    static std::shared_ptr<Model> LoadBicubicBezierPatch();
    static std::shared_ptr<Model> LoadBicubicBezierBowlPatch();
    static std::shared_ptr<Model> LoadBicubicBezierAsymmetricPatch();

    static std::shared_ptr<Model> LoadSquareModel();
    static std::shared_ptr<Model> LoadCAMMaterial();
    static std::shared_ptr<Model> LoadCubeModel();
    static std::shared_ptr<Model> LoadRoomModel();
    static std::shared_ptr<Model> LoadCubemapModel();
    static std::shared_ptr<Model> LoadLampModel();

    static std::shared_ptr<Model> LoadFloorModel();

    static std::shared_ptr<Model> LoadModel(std::string path);
    static std::shared_ptr<Model> LoadSphere(float radius = 2.0f);
    static std::shared_ptr<Model> LoadCircle(float radius = 2.0f);
    static std::shared_ptr<Model> CreateLine(const glm::vec3& p1,
                                             const glm::vec3& p2);

};
} // ifx

#endif //PROJECT_MODEL_FACTORY_H
