#ifndef PROJECT_MAIN_MENU_H
#define PROJECT_MAIN_MENU_H

#include <editor/window_view.h>
#include <memory>

namespace ifx {

class Editor;

class MainMenuViewItem;

class MainMenuWindowView : public WindowView {
public:
    MainMenuWindowView();
    ~MainMenuWindowView();

    virtual void Render() override;

    void RegisterEditor(std::shared_ptr<Editor> editor_);

protected:
    // overridden from View
    virtual void RenderContent() override;

private:
    void RenderFile();
    void RenderEdit();
    void RenderWindow();

    std::shared_ptr<Editor> editor_;

    std::unique_ptr<MainMenuViewItem> view_item_;
};

}

#endif //PROJECT_MAIN_MENU_H
