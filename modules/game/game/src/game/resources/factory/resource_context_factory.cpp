#include "game/resources/factory/resource_context_factory.h"

#include <resources/factory/resource_manager_factory.h>

#include <game/resources/resource_context.h>

namespace ifx {

ResourceContextFactory::ResourceContextFactory() {
    resource_manager_factory_
        = std::shared_ptr<ResourceManagerFactory>(
        new ResourceManagerFactory());
}

ResourceContextFactory::~ResourceContextFactory() {}

std::shared_ptr<ResourceContext> ResourceContextFactory::Create() {
    auto resource_creator = std::shared_ptr<ResourceContext>(
        new ResourceContext(resource_manager_factory_->Create()));
    return resource_creator;
}

ResourceContextFactory &ResourceContextFactory::SetResourceManagerFactory(
    std::shared_ptr<ResourceManagerFactory> factory) {
    resource_manager_factory_ = factory;
    return *this;
}

}