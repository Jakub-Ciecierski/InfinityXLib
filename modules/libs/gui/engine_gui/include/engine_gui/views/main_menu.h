#ifndef PROJECT_MAIN_MENU_H
#define PROJECT_MAIN_MENU_H

#include <engine_gui/view.h>

namespace ifx{

class MainMenu : public View {
public:
    MainMenu();
    ~MainMenu();

    // overridden from View
    void Render() override;

private:
};

}

#endif //PROJECT_MAIN_MENU_H
