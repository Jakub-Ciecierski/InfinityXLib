#ifndef PROJECT_RESOURCE_MANAGER_H
#define PROJECT_RESOURCE_MANAGER_H

#include <memory>

namespace ifx {

class ResourceMemoryCache;
class Resources;

class ResourceManager {
public:

    ResourceManager();
    ~ResourceManager();

    ResourceMemoryCache* resource_memory_cache(){
        return resource_memory_cache_.get();}
    Resources* resource_path(){return resource_path_.get();}
private:

    std::unique_ptr<ResourceMemoryCache> resource_memory_cache_;
    std::unique_ptr<Resources> resource_path_;
};

}
#endif //PROJECT_RESOURCE_MANAGER_H
