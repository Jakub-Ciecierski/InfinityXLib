#ifndef PROJECT_RESOURCE_MANAGER_FACTORY_H
#define PROJECT_RESOURCE_MANAGER_FACTORY_H

#include <memory>

namespace ifx {

class ResourceManager;
class ResourceFinder;
class Resources;

class ResourceManagerFactory {
public:
    ResourceManagerFactory() = default;

    ~ResourceManagerFactory() = default;

    std::shared_ptr<ResourceManager> Create();
private:

    std::shared_ptr<ResourceFinder> CreateModelFinder(Resources& resource);
    std::shared_ptr<ResourceFinder> CreateTextureFinder(Resources& resource);
};
}

#endif //PROJECT_RESOURCE_MANAGER_FACTORY_H
