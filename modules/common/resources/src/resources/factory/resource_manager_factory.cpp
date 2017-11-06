#include "resources/factory/resource_manager_factory.h"

#include <resources/resource_manager.h>
#include <resources/resource_finder.h>
#include <resources/resources.h>
#include <resources/resource_memory_cache.h>

#include <common/unique_ptr.h>

namespace ifx {

std::shared_ptr<ResourceManager> ResourceManagerFactory::Create() {
    auto resource_memory_cache = ifx::make_unique<ResourceMemoryCache>();
    auto resource_path = ifx::make_unique<Resources>();

    ResourceFinders resource_finders{
            CreateModelFinder(*resource_path),
            CreateTextureFinder(*resource_path)
    };

    return std::make_shared<ResourceManager>(
            resource_finders,
            std::move(resource_memory_cache),
            std::move(resource_path));
}

std::shared_ptr<ResourceFinder> ResourceManagerFactory::CreateModelFinder(
        Resources& resource){
    auto root_model = resource.GetResourceRoot(ResourceType::MODEL);
    std::vector<ResourceFinderRootDirectory> root_directories{
            ResourceFinderRootDirectory{root_model}
    };
    std::vector<ResourceFinderExtension> extensions{
            ResourceFinderExtension{"obj"},
            ResourceFinderExtension{"fbx"},
            ResourceFinderExtension{"mtl"},
            ResourceFinderExtension{"stl"}
    };

    auto resource_finder = std::make_shared<ResourceFinder>(
            root_directories, extensions);
    resource_finder->Update();

    return resource_finder;
}

std::shared_ptr<ResourceFinder> ResourceManagerFactory::CreateTextureFinder(
        Resources& resource
){
    auto root_model = resource.GetResourceRoot(ResourceType::MODEL);
    auto root_texture = resource.GetResourceRoot(ResourceType::TEXTURE);
    std::vector<ResourceFinderRootDirectory> root_directories{
            ResourceFinderRootDirectory{root_model},
            ResourceFinderRootDirectory{root_texture},
    };
    std::vector<ResourceFinderExtension> extensions{
            ResourceFinderExtension{"jpg"},
            ResourceFinderExtension{"png"}
    };

    auto resource_finder = std::make_shared<ResourceFinder>(
            root_directories, extensions);
    resource_finder->Update();

    return resource_finder;
}

}
