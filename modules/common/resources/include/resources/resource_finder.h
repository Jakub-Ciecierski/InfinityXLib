#ifndef PROJECT_RESOURCE_FINDER_H
#define PROJECT_RESOURCE_FINDER_H

#include <vector>
#include <string>

namespace ifx {

struct ResourceFinderExtension {
    // e.g. "jpg"
    std::string extension;
};

struct ResourceFinderRootDirectory{
    std::string root;
};

class ResourceFinder {
public:
    ResourceFinder(
            const std::vector<ResourceFinderRootDirectory>& root_directories,
            const std::vector<ResourceFinderExtension>& look_for_extensions);

    ~ResourceFinder() = default;

    const std::vector<std::string>& found_resources(){return found_resources_;}

    void Update();
private:
    void UpdateDirectory(const std::string& directory);

    bool IsCorrectFile(const std::string& file_name);
    bool EndsWith(const std::string &str,
                  const std::string &end);

    std::vector<ResourceFinderRootDirectory> root_directories_;
    std::vector<ResourceFinderExtension> look_for_extensions_;

    std::vector<std::string> found_resources_;
};
}


#endif //PROJECT_RESOURCE_FINDER_H
