#ifndef PROJECT_RESOURCE_VIEW_FACTORY_H
#define PROJECT_RESOURCE_VIEW_FACTORY_H

#include "editor/views/factory/view_factory.h"

namespace ifx {

class ResourceContext;
class ResourceFinder;

class ResourceViewFactory : public ViewFactory{
public:

    ResourceViewFactory(std::shared_ptr<ResourceContext> resource_context) ;
    ~ResourceViewFactory() = default;

    virtual std::shared_ptr<View> Create() override;

private:
    std::shared_ptr<ResourceContext> resource_context_;
};
}


#endif //PROJECT_RESOURCE_VIEW_FACTORY_H
