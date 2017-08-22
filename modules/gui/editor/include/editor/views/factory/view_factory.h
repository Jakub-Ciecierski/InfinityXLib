#ifndef PROJECT_VIEW_FACTORY_H
#define PROJECT_VIEW_FACTORY_H

#include <memory>

namespace ifx {

class View;

class ViewFactory {
public:
    ViewFactory() = default;
    virtual ~ViewFactory() = default;

    virtual std::shared_ptr<View> Create() = 0;
};
}

#endif //PROJECT_VIEW_FACTORY_H
