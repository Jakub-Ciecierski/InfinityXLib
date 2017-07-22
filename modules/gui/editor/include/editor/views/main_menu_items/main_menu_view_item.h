#ifndef PROJECT_VIEW_ITEM_H
#define PROJECT_VIEW_ITEM_H

#include <memory>

namespace ifx {

class Editor;
class Docker;
struct DockerSettings;

class MainMenuViewItem {
public:

    MainMenuViewItem();

    ~MainMenuViewItem();

    void Render(std::shared_ptr<Editor> editor);

private:

    void RenderShowWindows(std::shared_ptr<Editor> editor);

    void RenderDocker(std::shared_ptr<Docker> docker);
    void RenderDockerHeader(std::shared_ptr<Docker> docker,
                            DockerSettings& settings);
    void RenderDockerAutomaticScale(DockerSettings& settings);
    void RenderDockerManualScale(DockerSettings& settings);
    void RenderDockerFooter();

};
}


#endif //PROJECT_VIEW_ITEM_H
