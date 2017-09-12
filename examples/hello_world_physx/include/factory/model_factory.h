#ifndef PROJECT_MODEL_FACTORY_H
#define PROJECT_MODEL_FACTORY_H

#include <graphics/model/model.h>

#include <memory>

namespace ifx {

class ModelCreator;
class TextureCreator;

class ModelFactory {
public:

    ModelFactory(std::shared_ptr<ModelCreator>,
                 std::shared_ptr<TextureCreator> texture_creator);
    ~ModelFactory();

    std::shared_ptr<Model> LoadAsteroidModel();
    std::shared_ptr<Model> LoadNanoSuitModel();

    std::shared_ptr<Model> CreateQuad(int x, int y);

    std::shared_ptr<Model> LoadBicubicBezierSurfaceC0();
    std::shared_ptr<Model> LoadBicubicBezierPatch();
    std::shared_ptr<Model> LoadBicubicBezierBowlPatch();
    std::shared_ptr<Model> LoadBicubicBezierAsymmetricPatch();

    std::shared_ptr<Model> LoadSquareModel();
    std::shared_ptr<Model> LoadCAMMaterial();
    std::shared_ptr<Model> LoadCubeModel();
    std::shared_ptr<Model> LoadRoomModel();
    std::shared_ptr<Model> LoadCubemapModel();
    std::shared_ptr<Model> LoadLampModel();

    std::shared_ptr<Model> LoadFloorModel();

    std::shared_ptr<Model> LoadModel(std::string path);
    std::shared_ptr<Model> LoadSphere(float radius = 2.0f);
    std::shared_ptr<Model> LoadCircle(float radius = 2.0f);
    std::shared_ptr<Model> CreateLine(const glm::vec3 &p1,
                                      const glm::vec3 &p2);
private:
    std::shared_ptr<ModelCreator> model_creator_;
    std::shared_ptr<TextureCreator> texture_creator_;
};
} // ifx

#endif //PROJECT_MODEL_FACTORY_H
