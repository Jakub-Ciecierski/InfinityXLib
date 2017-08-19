#ifndef PROJECT_DOCKER_H
#define PROJECT_DOCKER_H

#include <memory>

typedef int ImGuiWindowFlags;

namespace ifx {

class WindowView;
class Window;

enum class DockPosition{
    Left, Right, Top, Bottom, SoftBody
};

struct DockerSettings{
    float left_view_width;
    float right_view_width;
    float bottom_view_height;

    // Scale automatically based on window size and scale coefficient
    bool is_automatic_scale;
    float automatic_scale;

    bool soft_body_window_full;
};

/**
 * Docks the given views in their respective places based on
 * current window size.
 */
class Docker {
public:

    Docker(std::shared_ptr<Window> window);

    ~Docker();
    std::shared_ptr<Window> window(){return window_;}

    const DockerSettings& docker_settings(){return docker_settings_;}
    void docker_settings(const DockerSettings& settings){
        docker_settings_ = settings;
    }

    bool IsEnabled(){return is_enabled_;}

    void Enable();
    void Disable();

    void RegisterView(std::shared_ptr<WindowView> view,
                      const DockPosition &dock_position);
    void Dock(std::shared_ptr<WindowView> view);

private:
    void SetDisabledFlags();
    void SetEnabledFlags();

    void SetFlags(ImGuiWindowFlags flags);

    void UpdateAutomaticSize();

    void DockLeft();
    void DockRight();
    void DockTop();
    void DockBottom();
    void DockSoftBodyWindow();

    std::shared_ptr<Window> window_;

    std::shared_ptr<WindowView> left_window_view_;
    std::shared_ptr<WindowView> right_window_view_;
    std::shared_ptr<WindowView> top_window_view_;
    std::shared_ptr<WindowView> bottom_window_view_;
    std::shared_ptr<WindowView> soft_body_window_view_;

    bool is_enabled_;

    DockerSettings docker_settings_;
};
}


#endif //PROJECT_DOCKER_H
