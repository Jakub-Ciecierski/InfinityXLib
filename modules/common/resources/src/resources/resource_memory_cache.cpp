#include "resources/resource_memory_cache.h"

#include "resources/resource.h"

namespace ifx {

ResourceMemoryCache::ResourceMemoryCache() {}

ResourceMemoryCache::~ResourceMemoryCache() {}

bool ResourceMemoryCache::Add(std::shared_ptr<Resource> resource) {
    if (Exists(resource->filepath()) ||
        resource->filepath().compare(NO_FILEPATH) == 0)
        return false;
    resources_.push_back(resource);
    return true;
}

std::shared_ptr<Resource> ResourceMemoryCache::Get(std::string filepath) {
    for (auto &resource : resources_) {
        if (!filepath.compare(resource->filepath()))
            return resource;
    }
    return nullptr;
}

bool ResourceMemoryCache::Exists(std::string filepath) {
    for (auto &resource : resources_) {
        if (!filepath.compare(resource->filepath()))
            return true;
    }
    return false;
}

void ResourceMemoryCache::ClearUnusedResources() {
    std::vector<std::shared_ptr<Resource>> tmp_resources;

    for (auto &resource : resources_) {
        if (resource.use_count() > 1)
            tmp_resources.push_back(resource);
    }

    resources_ = tmp_resources;
}

void ResourceMemoryCache::ClearAll() {
    resources_.clear();
}

std::vector<std::shared_ptr<Resource>> ResourceMemoryCache::GetResources(
    ResourceType type) {
    std::vector<std::shared_ptr<Resource>> resources;
    for (auto &resource : resources_) {
        if (resource->type() == type)
            resources.push_back(resource);
    }
    return resources;
}

}