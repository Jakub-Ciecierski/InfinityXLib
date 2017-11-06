#include "resources/resource_manager.h"

#include <resources/resource_memory_cache.h>
#include <resources/resources.h>
#include "resources/resource_finder.h"

namespace ifx {

ResourceManager::ResourceManager(
        const ResourceFinders &resource_finders,
        std::unique_ptr<ResourceMemoryCache> resource_memory_cache,
        std::unique_ptr<Resources> resource_path) :
        resource_finders_(resource_finders),
        resource_memory_cache_(std::move(resource_memory_cache)),
        resource_path_(std::move(resource_path)) {}

}