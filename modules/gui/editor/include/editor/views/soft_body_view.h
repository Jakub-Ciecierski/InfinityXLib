#ifndef PROJECT_SOFT_BODY_VIEW_H
#define PROJECT_SOFT_BODY_VIEW_H

#include <memory>
#include <vector>

#include <editor/view.h>
#include <editor/views/scene_views/scene_view_observer.h>
#include <editor/views/soft_body_views/soft_body_structers.h>

namespace ifx {

class GameUpdater;
class GameObject;
class RenderingEffect;
class RenderComponent;

class SoftBodyScreenView;
class SoftBodySelector;

class SoftBodySolverView;
class SoftBodyBoundaryConditionsView;
class SoftBodyMeshingView;
class SoftBodyRenderingView;
class SoftBodyMaterialView;
class SoftBodyLoadView;
class SoftBodyGuideView;

template<class T>
class SoftBodyFEMComponent;

struct SoftBodyViews{
    unsigned int selected = 0;

    const std::string guide_name = "Guide";
    static constexpr unsigned int guide_id = 0;

    const std::string meshing_name = "Meshing";
    static constexpr unsigned int meshing_id = 1;

    const std::string material_name = "Material";
    static constexpr unsigned int material_id = 2;

    const std::string boudary_conditions_name = "Boundary Conditions";
    static constexpr unsigned int boudary_conditions_id = 3;

    const std::string load_name = "Load";
    static constexpr unsigned int load_id = 4;

    const std::string rendering_name = "Rendering";
    static constexpr unsigned int rendering_id = 5;

    const std::string solver_name = "Solver";
    static constexpr unsigned int solver_id = 6;

    const std::vector<std::string> names{
        guide_name,
        meshing_name,
        material_name,
        boudary_conditions_name,
        load_name,
        rendering_name,
        solver_name
    };

    const int GetID(std::string name)  {
        for (unsigned int i = 0; i < names.size(); i++) {
            if (names[i] == name) {
                return i;
            }
        }
        return -1;
    }

    const std::string GetSelectedName(){
        if(selected < 0 || selected >= names.size()){
            return "";
        }
        return names[selected];
    }

    const std::string GetName(unsigned int id)  {
        if(id < 0 || id >= names.size()){
            return "";
        }
        return names[id];
    }
};

class SoftBodyView : public View, public SceneViewObserver {
public:
    SoftBodyView(std::unique_ptr<GameUpdater> game_updater,
                 const SoftBodyRenderingEffects &rendering_effects);
    ~SoftBodyView() = default;

    bool Terminate() override;

    virtual void Render() override;

    void OnSetSelectedGameObject(
        std::shared_ptr<GameObject> selected_game_object) override;

    SoftBodyScreenView& screen_view(){return *screen_view_;}

private:
    void RenderLeftColumn();
    void RenderRightColumn();

    std::unique_ptr<GameUpdater> game_updater_;

    SoftBodyRenderingEffects rendering_effects_;
    SoftBodyObjects soft_body_objects_;

    bool first_render_;

    SoftBodyViews soft_body_views;

    std::unique_ptr<SoftBodyScreenView> screen_view_;

    std::unique_ptr<SoftBodySelector> selector_;

    std::unique_ptr<SoftBodyGuideView> soft_body_guide_view_;
    std::unique_ptr<SoftBodyMeshingView> meshing_view_;
    std::unique_ptr<SoftBodyRenderingView> rendering_view_;
    std::unique_ptr<SoftBodyMaterialView> material_view_;
    std::unique_ptr<SoftBodyBoundaryConditionsView> boundarary_conditions_view_;
    std::unique_ptr<SoftBodyLoadView> load_view_;
    std::unique_ptr<SoftBodySolverView> solver_view_;

    std::shared_ptr<SoftBodyFEMComponent<double>> soft_body_fem_;
};
}

#endif //PROJECT_SOFT_BODY_VIEW_H
