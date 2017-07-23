#ifndef PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_PARAMETRIC_EQUATION_H
#define PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_PARAMETRIC_EQUATION_H

#include <memory>

namespace ifx {

class ResourceContext;
class GameObject;
class ParametricEquationExpressions;
class RenderComponent;
class ParametricEquation;

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
    void RenderConstants();
    void RenderVariables();
    void RenderPrecision();
    void RenderFooter(std::shared_ptr<ResourceContext> resource_creator,
                      std::shared_ptr<GameObject> game_object);

    bool TryCreateRenderComponent(
            std::shared_ptr<ResourceContext> resource_creator,
            std::shared_ptr<GameObject> game_object);
    std::shared_ptr<RenderComponent> CreateRenderComponent(
            std::unique_ptr<ParametricEquation> parametric_equation,
            std::shared_ptr<ResourceContext> resource_creator);
    void RenderErrorWindow();

    void RenderExampleEquations();

    void RenderInputExpression(
            std::string name, std::string& expression);

    std::unique_ptr<ParametricEquationExpressions>
            parametric_equation_expressions_;

    bool render_error_window_;
    std::string error_message_;
};
}


#endif //PROJECT_CONTEXT_MENU_ADD_RENDER_OBJECT_PARAMETRIC_EQUATION_H
