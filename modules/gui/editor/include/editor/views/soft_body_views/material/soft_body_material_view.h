#ifndef PROJECT_SOFT_BODY_MATERIAL_VIEW_H
#define PROJECT_SOFT_BODY_MATERIAL_VIEW_H

#include <memory>
#include <RTFEM/FEM/Material.h>

namespace ifx {

template<class T>
class SoftBodyFEMComponent;

class SoftBodyMaterialView {
public:
    SoftBodyMaterialView() = default;
    ~SoftBodyMaterialView() = default;

    void Render(rtfem::Material<double>& material);
private:
    void RenderMaterial(rtfem::Material<double>& material);
};

}

#endif //PROJECT_SOFT_BODY_MATERIAL_VIEW_H
