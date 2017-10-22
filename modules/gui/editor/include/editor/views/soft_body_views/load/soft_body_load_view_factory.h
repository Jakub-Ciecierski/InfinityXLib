#ifndef PROJECT_SOFT_BODY_LOAD_VIEW_FACTORY_H
#define PROJECT_SOFT_BODY_LOAD_VIEW_FACTORY_H

#include <memory>
#include <math/math_ifx.h>

namespace ifx {

struct EngineArchitecture;
class SoftBodyLoadView;
class RenderingEffect;
class SoftBodyPicker;
class Mesh;

class SoftBodyLoadViewFactory {
public:
    SoftBodyLoadViewFactory() = default;
    ~SoftBodyLoadViewFactory() = default;

    std::unique_ptr<SoftBodyLoadView> Create(
        std::shared_ptr<EngineArchitecture> new_engine_architecture,
        std::shared_ptr<EngineArchitecture> old_engine_architecture,
        std::shared_ptr<SoftBodyPicker> soft_body_picker
    );

private:
    std::shared_ptr<RenderingEffect> CreateRenderingEffect(
        std::shared_ptr<EngineArchitecture> old_engine_architecture);

    std::unique_ptr<Mesh> CreateLine(const glm::vec3 &p1,
                                     const glm::vec3 &p2);
};

}

#endif //PROJECT_SOFT_BODY_LOAD_VIEW_FACTORY_H
