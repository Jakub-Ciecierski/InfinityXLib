#include "game/resources/resource_context.h"

#include <resources/resource_manager.h>

#include <graphics/model/model_creator.h>
#include <graphics/shaders/program_creator.h>
#include <graphics/shaders/textures/texture_creator.h>

namespace ifx {

ResourceContext::ResourceContext(
    std::shared_ptr<ResourceManager> resource_manager) :
    resource_manager_(resource_manager) {
    program_creator_.reset(new ProgramCreator(resource_manager_));
    model_creator_.reset(new ModelCreator(resource_manager_));
    texture_creator_.reset(new TextureCreator(resource_manager_));
}

}
