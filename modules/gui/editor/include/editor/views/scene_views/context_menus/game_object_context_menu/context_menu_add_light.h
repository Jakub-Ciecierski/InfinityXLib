#ifndef PROJECT_CONTEXT_MENU_ADD_LIGHT_H
#define PROJECT_CONTEXT_MENU_ADD_LIGHT_H

#include <memory>

namespace ifx {

class ResourceContext;
class GameObject;

class ContextMenuAddLight {
public:

    ContextMenuAddLight() = default;

    ~ContextMenuAddLight() = default;

    void Render(std::shared_ptr<ResourceContext> resource_creator,
                std::shared_ptr<GameObject> game_object);

private:
};
}

#endif //PROJECT_CONTEXT_MENU_ADD_LIGHT_H
