#include "resources/resource_manager.h"

#include <resources/resource_memory_cache.h>
#include <resources/resources.h>

namespace ifx{

ResourceManager::ResourceManager(){
    resource_memory_cache_.reset(new ResourceMemoryCache());
    resource_path_.reset(new Resources());
}

ResourceManager::~ResourceManager(){}

}