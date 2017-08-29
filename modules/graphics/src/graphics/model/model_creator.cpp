#include "graphics/model/model_creator.h"

#include <graphics/model/model.h>

#include <resources/resource_manager.h>
#include <resources/resource_memory_cache.h>

namespace ifx {

ModelCreator::ModelCreator(std::shared_ptr<ResourceManager> resource_manager)
        : resource_manager_(resource_manager){}

std::shared_ptr<Model> ModelCreator::MakeModel(
        std::string filepath,
        std::vector<std::unique_ptr<Mesh>> meshes) {
    std::shared_ptr<Model> model
            = std::static_pointer_cast<Model>(
                    resource_manager_->resource_memory_cache()->Get(filepath));
    if (!model) {
        model = std::shared_ptr<Model>(new Model(filepath, std::move(meshes)));
    }
    resource_manager_->resource_memory_cache()->Add(model);

    return model;
}

std::shared_ptr<Model> ModelCreator::MakeModel(
        std::string filepath,
        std::unique_ptr<Mesh> mesh) {
    std::shared_ptr<Model> model
            = std::static_pointer_cast<Model>(
                    resource_manager_->resource_memory_cache()->Get(filepath));
    std::vector<std::unique_ptr<Mesh>> meshes;
    meshes.push_back(std::move(mesh));

    if (!model) {
        model = std::shared_ptr<Model>(new Model(filepath, std::move(meshes)));
    }
    resource_manager_->resource_memory_cache()->Add(model);

    return model;
}

};

