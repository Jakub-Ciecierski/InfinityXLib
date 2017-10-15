#ifndef PROJECT_SOFT_BODY_PICKER_FACTORY_H
#define PROJECT_SOFT_BODY_PICKER_FACTORY_H

#include <memory>

namespace ifx {

struct EngineArchitecture;
class SoftBodyPicker;
class BoxCasting;
class RenderingEffect;

class SoftBodyPickerFactory {
public:
    SoftBodyPickerFactory() = default;
    ~SoftBodyPickerFactory() = default;

    std::unique_ptr<SoftBodyPicker> Create(
        std::shared_ptr<EngineArchitecture> new_engine_architecture,
        std::shared_ptr<EngineArchitecture> old_engine_architecture
    );
private:

    std::unique_ptr<BoxCasting> CreateBoxCasting(
        std::shared_ptr<EngineArchitecture> new_engine_architecture,
        std::shared_ptr<EngineArchitecture> old_engine_architecture
    );
    std::shared_ptr<RenderingEffect> CreateRenderingEffect(
        std::shared_ptr<EngineArchitecture> old_engine_architecture
    );
};

}

#endif //PROJECT_SOFT_BODY_PICKER_FACTORY_H
