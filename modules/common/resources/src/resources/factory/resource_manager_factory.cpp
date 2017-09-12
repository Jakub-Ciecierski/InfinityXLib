#include "resources/factory/resource_manager_factory.h"

#include <resources/resource_manager.h>

namespace ifx {

ResourceManagerFactory::ResourceManagerFactory() {}

ResourceManagerFactory::~ResourceManagerFactory() {}

std::shared_ptr<ResourceManager> ResourceManagerFactory::Create() {
    auto resource_manager = std::shared_ptr<ResourceManager>(
        new ResourceManager());
    return resource_manager;
}

}