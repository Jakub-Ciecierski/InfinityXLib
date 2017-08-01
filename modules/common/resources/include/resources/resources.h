#ifndef PROJECT_RESOURCES_H
#define PROJECT_RESOURCES_H

#include <string>

namespace ifx {

enum class ResourceType{
    MODEL, SHADER, TEXTURE
};

/**
 * Static class responsible for concatenating given resource name
 * with the full path to resource directory
 */
class Resources {
public:
    Resources();
    ~Resources() = default;

    std::string GetResourcePath(std::string name, ResourceType type);
    std::string GetResourceRoot(ResourceType type);

private:
    void InitResourcePath();
    std::string ResouceTypePath(ResourceType type);
    std::string ConcatenatePath(std::string path1, std::string path2);

    std::string resource_root_path_;


};

}

#endif //PROJECT_RESOURCES_H
