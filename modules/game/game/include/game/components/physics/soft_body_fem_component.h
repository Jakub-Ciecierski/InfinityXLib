#ifndef PROJECT_SOFT_BODY_FEM_COMPONENT_H
#define PROJECT_SOFT_BODY_FEM_COMPONENT_H

#include <game/game_component.h>
#include <physics/soft_body/soft_body_fem.h>

namespace ifx {

class RenderComponent;

template<class T>
class SoftBodyFEMComponent : public GameComponent, public SoftBodyFEM<T> {
public:
    SoftBodyFEMComponent(std::unique_ptr<rtfem::FEMModel<T>> fem_model,
                         std::shared_ptr<RenderComponent> render_component);
    ~SoftBodyFEMComponent() = default;

    std::shared_ptr<RenderComponent> render_component(){
        return render_component_;}

    void Update(float time_delta) override;

private:
    void UpdateVBOPositions();

    std::shared_ptr<RenderComponent> render_component_;
};

}

#endif //PROJECT_SOFT_BODY_FEM_COMPONENT_H
