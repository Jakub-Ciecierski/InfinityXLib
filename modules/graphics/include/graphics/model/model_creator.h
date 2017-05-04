#ifndef PROJECT_MODEL_CREATOR_H
#define PROJECT_MODEL_CREATOR_H

#include <memory>
#include <vector>

namespace ifx {

class Model;
class Mesh;
class ResourceManager;

class ModelCreator {
public:

    ModelCreator(std::shared_ptr<ResourceManager> resource_manager);

    ~ModelCreator();

    std::shared_ptr<ResourceManager> resource_manager(){
        return resource_manager_;}

    std::shared_ptr<Model> MakeModel(
            std::string filepath,
            std::vector<std::unique_ptr<Mesh>> meshes);

private:
    std::shared_ptr<ResourceManager> resource_manager_;

};
}

#endif //PROJECT_MODEL_CREATOR_H
