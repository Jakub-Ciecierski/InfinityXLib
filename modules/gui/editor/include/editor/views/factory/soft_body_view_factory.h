#ifndef PROJECT_SOFT_BODY_VIEW_FACTORY_H
#define PROJECT_SOFT_BODY_VIEW_FACTORY_H

#include <memory>

#include "editor/views/factory/view_factory.h"

namespace ifx {

class SoftBodyView;

struct GameArchitecture;

class SoftBodyViewFactory : public ViewFactory {
public:
    SoftBodyViewFactory(std::shared_ptr<GameArchitecture> game_architecture);
    ~SoftBodyViewFactory() = default;

    virtual std::shared_ptr<View> Create() override;
private:
    std::shared_ptr<GameArchitecture> game_architecture_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_FACTORY_H
