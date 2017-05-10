#ifndef PROJECT_CONTROLS_FACTORY_H
#define PROJECT_CONTROLS_FACTORY_H

#include <memory>

namespace ifx {

class Controls;
class ControlContext;
class ControllerContainerFactory;

class ControlsFactory {
public:

    ControlsFactory();
    ~ControlsFactory();

    ControlsFactory& SetInputContainerFactory(
            std::shared_ptr<ControllerContainerFactory> factory){
        controller_container_factory_ = factory;
        return *this;
    }

    std::shared_ptr<Controls> Create(std::shared_ptr<ControlContext>);

private:
    void CreateDefaultFactories();

    std::shared_ptr<ControllerContainerFactory>
            controller_container_factory_;
};
}


#endif //PROJECT_CONTROLS_FACTORY_H
