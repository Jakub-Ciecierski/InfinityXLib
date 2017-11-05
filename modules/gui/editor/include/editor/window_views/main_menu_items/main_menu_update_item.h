#ifndef PROJECT_MAIN_MENU_UPDATE_ITEM_H
#define PROJECT_MAIN_MENU_UPDATE_ITEM_H

#include <memory>

namespace ifx {

struct EngineArchitecture;

class Updatable;

class MainMenuUpdateItem {
public:
    MainMenuUpdateItem() = default;
    ~MainMenuUpdateItem() = default;

    void Render(EngineArchitecture& engine_architecture);
private:
    void RenderEngineUpdateSettings(EngineArchitecture& engine_architecture);
    void RenderUpdateSettings(std::shared_ptr<Updatable> updatable,
                              std::string name);
    void RenderFooter();
};

}

#endif //PROJECT_MAIN_MENU_UPDATE_ITEM_H
