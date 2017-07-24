#include "factory/model_factory.h"

#include <factory/mesh_factory.h>
#include <graphics/model_loader/model_loader.h>
#include <resources/resources.h>
#include <graphics/model/model_creator.h>
#include <graphics/shaders/textures/texture_creator.h>

#include <resources/resource_manager.h>
#include <resources/resources.h>

#include <memory>

namespace ifx {

using namespace glm;
using namespace std;

ModelFactory::ModelFactory(std::shared_ptr<ModelCreator> model_creator,
                           std::shared_ptr<TextureCreator> texture_creator) :
        model_creator_(model_creator),
        texture_creator_(texture_creator){}

ModelFactory::~ModelFactory() {}

std::shared_ptr<Model> ModelFactory::LoadAsteroidModel() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();
    std::string path
        = resource_path->GetResourcePath("asteroid/rock.obj",
                                          ResourceType::MODEL);
    return LoadModel(path);
}

std::shared_ptr<Model> ModelFactory::LoadNanoSuitModel() {
    auto resource_path = texture_creator_->resource_manager()->resource_path();
    std::string path
        = resource_path->GetResourcePath("nanosuit/nanosuit.obj",
                                                   ResourceType::MODEL);
    return LoadModel(path);
}

std::shared_ptr<Model> ModelFactory::CreateQuad(int x, int y){
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.CreateQuad(x,y)));

    return model_creator_->MakeModel("Quad", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierSurfaceC0() {
/*
    Mesh *mesh1 = meshLoader.LoadBicubicBezierPatch(0, 0, 0.0f, 3, 0);
    Mesh *mesh2 = meshLoader.LoadBicubicBezierPatch(2, 0, 2.0f, 3, 1);
    Mesh *mesh3 = meshLoader.LoadBicubicBezierPatch(4, 0, 1.5f, 3, 2);
    Mesh *mesh4 = meshLoader.LoadBicubicBezierPatch(6, 0, 1.5f, 3, 3);

    Mesh *mesh5 = meshLoader.LoadBicubicBezierPatch(0, 2, 0.2f, 2, 0);
    Mesh *mesh6 = meshLoader.LoadBicubicBezierPatch(2, 2, 0.5f, 2, 1);
    Mesh *mesh7 = meshLoader.LoadBicubicBezierPatch(4, 2, 2.5f, 2, 2);
    Mesh *mesh8 = meshLoader.LoadBicubicBezierPatch(6, 2, -1.5f, 2, 3);

    Mesh *mesh9 = meshLoader.LoadBicubicBezierPatch(0, 4, 0.4f, 1, 0);
    Mesh *mesh10 = meshLoader.LoadBicubicBezierPatch(2, 4, 1.5f, 1, 1);
    Mesh *mesh11 = meshLoader.LoadBicubicBezierPatch(4, 4, -1.5f, 1, 2);
    Mesh *mesh12 = meshLoader.LoadBicubicBezierPatch(6, 4, 1.9f, 1, 3);

    Mesh *mesh13 = meshLoader.LoadBicubicBezierPatch(0, 6, 0.3f, 0, 0);
    Mesh *mesh14 = meshLoader.LoadBicubicBezierPatch(2, 6, 1.5f, 0, 1);
    Mesh *mesh15 = meshLoader.LoadBicubicBezierPatch(4, 6, 1.0f, 0, 2);
    Mesh *mesh16 = meshLoader.LoadBicubicBezierPatch(6, 6, -0.5f, 0, 3);

    std::vector<std::unique_ptr<Mesh>> meshes{
            std::unique_ptr<Mesh>(mesh1),
            std::unique_ptr<Mesh>(mesh2),
            std::unique_ptr<Mesh>(mesh3),
            std::unique_ptr<Mesh>(mesh4),
            std::unique_ptr<Mesh>(mesh5),
            std::unique_ptr<Mesh>(mesh6),
            std::unique_ptr<Mesh>(mesh7),
            std::unique_ptr<Mesh>(mesh8),
            std::unique_ptr<Mesh>(mesh9),
            std::unique_ptr<Mesh>(mesh10),
            std::unique_ptr<Mesh>(mesh11),
            std::unique_ptr<Mesh>(mesh12),
            std::unique_ptr<Mesh>(mesh13),
            std::unique_ptr<Mesh>(mesh14),
            std::unique_ptr<Mesh>(mesh15),
            std::unique_ptr<Mesh>(mesh16)
    };
    return Model::MakeModel("BicubicBezierSurfaceC0", std::move(meshes));
    */

    return nullptr;
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierPatch() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadBicubicBezierPatch(-1, 1, 1.5f)));

    return model_creator_->MakeModel("BicubicBezierPatch",
                                     std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierBowlPatch() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadBicubicBezierPatch(-1, 1, 1.5f)));

    return model_creator_->MakeModel("BicubicBezierBowlPatch", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadBicubicBezierAsymmetricPatch() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadBicubicBezierAsymmetricPatch()));

    return model_creator_->MakeModel("BicubicBezierAsymmetricPatch", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadSquareModel() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadPatch()));

    return model_creator_->MakeModel("SquareModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadCAMMaterial() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadCAMMaterial()));

    return model_creator_->MakeModel("CubeModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadCubeModel() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadCube()));

    return model_creator_->MakeModel(ifx::NO_FILEPATH, std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadRoomModel() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadRoom()));

    return model_creator_->MakeModel("RoomModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadCubemapModel() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadCubemap()));

    return model_creator_->MakeModel("CubemapModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadLampModel() {
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadLamp()));

    return model_creator_->MakeModel("LampModel", std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadModel(std::string path) {
    return ModelLoader(path, model_creator_, texture_creator_).loadModel();
}

std::shared_ptr<Model> ModelFactory::LoadFloorModel(){
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadFloor()));

    return model_creator_->MakeModel(NO_FILEPATH, std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadSphere(float radius){
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadSphere(radius)));

    return model_creator_->MakeModel(ifx::NO_FILEPATH, std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::LoadCircle(float radius){
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.LoadCircle(radius)));

    return model_creator_->MakeModel(ifx::NO_FILEPATH, std::move(meshes));
}

std::shared_ptr<Model> ModelFactory::CreateLine(const glm::vec3& p1,
                                                const glm::vec3& p2){
    MeshFactory mesh_factory(texture_creator_);

    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh_factory.CreateLine(p1,p2)));

    return model_creator_->MakeModel(ifx::NO_FILEPATH, std::move(meshes));
}
} // ifx