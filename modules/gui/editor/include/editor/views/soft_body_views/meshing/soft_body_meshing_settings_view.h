#ifndef PROJECT_SOFT_BODY_MESHING_SETTINGS_VIEW_H
#define PROJECT_SOFT_BODY_MESHING_SETTINGS_VIEW_H

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>

namespace ifx {

class SoftBodyMeshingSettingsView {
public:
    SoftBodyMeshingSettingsView() = default;
    ~SoftBodyMeshingSettingsView() = default;

    const rtfem::TetrahedralizationOptions &rtfem_options() {
        return rtfem_options_;
    }

    void Render();
private:
    rtfem::TetrahedralizationOptions rtfem_options_;
};

}

#endif //PROJECT_SOFT_BODY_MESHING_SETTINGS_VIEW_H
