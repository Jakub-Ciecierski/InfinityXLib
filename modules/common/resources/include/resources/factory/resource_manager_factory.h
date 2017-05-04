#ifndef PROJECT_RESOURCE_MANAGER_FACTORY_H
#define PROJECT_RESOURCE_MANAGER_FACTORY_H

#include <memory>

namespace ifx {

class ResourceManager;

class ResourceManagerFactory {
public:
    ResourceManagerFactory();

    ~ResourceManagerFactory();

    std::shared_ptr<ResourceManager> Create();
private:
};
}

#endif //PROJECT_RESOURCE_MANAGER_FACTORY_H
