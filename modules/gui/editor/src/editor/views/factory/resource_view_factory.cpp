#include "editor/views/factory/resource_view_factory.h"

#include <game/resources/resource_context.h>

#include <resources/resource_finder.h>
#include <resources/resource_manager.h>
#include <resources/resource.h>

#include <editor/views/resource_view.h>
#include "editor/views/resource_views/resource_model_view.h"
#include "editor/views/resource_views/resource_texture_view.h"

#include <common/unique_ptr.h>

namespace ifx {

ResourceViewFactory::ResourceViewFactory(
        std::shared_ptr<ResourceContext> resource_context) :
        resource_context_(resource_context){}

std::shared_ptr<View> ResourceViewFactory::Create(){
    auto resource_view = std::make_shared<ResourceView>(resource_context_);
    return resource_view;
}

}
