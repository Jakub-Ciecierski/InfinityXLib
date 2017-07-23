#ifndef PROJECT_PARAMETRIC_EQUATION_EXPRESSIONS_FACTORY_H
#define PROJECT_PARAMETRIC_EQUATION_EXPRESSIONS_FACTORY_H

#include <memory>

namespace ifx {

class ParametricEquationExpressions;

class ParametricEquationExpressionsFactory {
public:

    ParametricEquationExpressionsFactory();

    ~ParametricEquationExpressionsFactory();

    std::unique_ptr<ParametricEquationExpressions> CreateSphere();
    std::unique_ptr<ParametricEquationExpressions> CreateTorus();

private:
};
}


#endif //PROJECT_PARAMETRIC_EQUATION_EXPRESSIONS_FACTORY_H
