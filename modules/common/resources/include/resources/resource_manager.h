#ifndef PROJECT_RESOURCE_MANAGER_H
#define PROJECT_RESOURCE_MANAGER_H

#include <memory>

namespace ifx {

class ResourceMemoryCache;
class Resources;
class ResourceFinder;

struct ResourceFinders{
    std::shared_ptr<ResourceFinder> model_finder_;
    std::shared_ptr<ResourceFinder> texture_finder_;
};

class ResourceManager {
public:

    ResourceManager(const ResourceFinders &resource_finders,
                    std::unique_ptr<ResourceMemoryCache> resource_memory_cache,
                    std::unique_ptr<Resources> resource_path);
    ~ResourceManager() = default;

    ResourceMemoryCache *resource_memory_cache() {
        return resource_memory_cache_.get();
    }
    Resources *resource_path() { return resource_path_.get(); }

    ResourceFinders& resource_finders(){return resource_finders_;}
private:
    ResourceFinders resource_finders_;

    std::unique_ptr<ResourceMemoryCache> resource_memory_cache_;
    std::unique_ptr<Resources> resource_path_;

};

}
#endif //PROJECT_RESOURCE_MANAGER_H
