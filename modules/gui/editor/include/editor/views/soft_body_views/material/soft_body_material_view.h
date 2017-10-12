#ifndef PROJECT_SOFT_BODY_MATERIAL_VIEW_H
#define PROJECT_SOFT_BODY_MATERIAL_VIEW_H

#include <memory>

namespace ifx {

template<class T>
class SoftBodyFEMComponent;

class SoftBodyMaterialView {
public:
    SoftBodyMaterialView() = default;
    ~SoftBodyMaterialView() = default;

    void Render(std::shared_ptr<SoftBodyFEMComponent<double>>);
private:
    void RenderMaterial(std::shared_ptr<SoftBodyFEMComponent<double>>);
};

}

#endif //PROJECT_SOFT_BODY_MATERIAL_VIEW_H
