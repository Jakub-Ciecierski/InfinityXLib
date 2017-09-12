#ifndef PROJECT_RESOURCE_CREATOR_FACTORY_H
#define PROJECT_RESOURCE_CREATOR_FACTORY_H

#include <memory>

namespace ifx {

class ResourceManagerFactory;
class ResourceContext;

class ResourceContextFactory {
public:

    ResourceContextFactory();

    ~ResourceContextFactory();

    std::shared_ptr<ResourceContext> Create();

    ResourceContextFactory &SetResourceManagerFactory(
        std::shared_ptr<ResourceManagerFactory> factory);

private:
    std::shared_ptr<ResourceManagerFactory> resource_manager_factory_;
};
}

#endif //PROJECT_RESOURCE_CREATOR_FACTORY_H
