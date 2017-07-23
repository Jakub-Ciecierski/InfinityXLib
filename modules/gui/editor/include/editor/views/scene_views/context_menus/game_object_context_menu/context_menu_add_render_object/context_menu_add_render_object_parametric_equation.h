#ifndef PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_PARAMETRIC_EQUATION_H
#define PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_PARAMETRIC_EQUATION_H

#include <memory>

namespace ifx {

class ResourceContext;
class GameObject;
class ParametricEquationExpressions;
class RenderComponent;

class ContextMenuAddRenderObjectParametricEquation {
public:

    ContextMenuAddRenderObjectParametricEquation();

    ~ContextMenuAddRenderObjectParametricEquation();

    void Render(std::shared_ptr<ResourceContext> resource_creator,
                std::shared_ptr<GameObject> game_object);
private:
    std::unique_ptr<ParametricEquationExpressions>
    CreateDefaultParametricEquationExpression();

    void RenderWindow(std::shared_ptr<ResourceContext> resource_creator,
                      std::shared_ptr<GameObject> game_object);
    void RenderExpressions();
    void RenderVariables();
    void RenderPrecision();
    void RenderFooter(std::shared_ptr<ResourceContext> resource_creator,
                      std::shared_ptr<GameObject> game_object);

    std::shared_ptr<RenderComponent> CreateRenderObject(
            std::shared_ptr<ResourceContext> resource_creator);

    void RenderInputExpression(
            std::string name, std::string& expression);

    std::unique_ptr<ParametricEquationExpressions>
            parametric_equation_expressions_;
};
}


#endif //PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_PARAMETRIC_EQUATION_H
