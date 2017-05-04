#ifndef PROJECT_RESOURCE_CREATOR_H
#define PROJECT_RESOURCE_CREATOR_H

#include <memory>

namespace ifx {

class ResourceManager;

class ProgramCreator;
class ModelCreator;
class TextureCreator;

class ResourceContext {
public:
    ResourceContext(std::shared_ptr<ResourceManager>);

    ~ResourceContext();

    std::shared_ptr<ProgramCreator> program_creator(){return program_creator_;}
    std::shared_ptr<ModelCreator> model_creator(){return model_creator_;}
    std::shared_ptr<TextureCreator> texture_creator() {return texture_creator_;}

private:

    std::shared_ptr<ProgramCreator> program_creator_;
    std::shared_ptr<ModelCreator> model_creator_;
    std::shared_ptr<TextureCreator> texture_creator_;

    std::shared_ptr<ResourceManager> resource_manager_;
};
}

#endif //PROJECT_RESOURCE_CREATOR_H
