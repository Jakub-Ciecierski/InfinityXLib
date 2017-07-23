#include <graphics/model_loader/parametric_loader/factory/parametric_equation_expressions_factory.h>

#include <graphics/model_loader/parametric_loader/parametric_interpreter.h>

namespace ifx {

ParametricEquationExpressionsFactory::ParametricEquationExpressionsFactory(){}

ParametricEquationExpressionsFactory::~ParametricEquationExpressionsFactory(){}

std::unique_ptr<ParametricEquationExpressions>
ParametricEquationExpressionsFactory::CreateSphere(){
    auto expression = std::unique_ptr<ParametricEquationExpressions>(
            new ParametricEquationExpressions());
    expression->constants.push_back(
            ParametricEquationConstantExpression{"r",1});
    expression->Px = "r * cos(u) * sin(v)";
    expression->Py = "r * sin(u) * sin(v)";
    expression->Pz = "r * cos(v)";

    expression->Px_du = "r * -sin(u) * sin(v)";
    expression->Py_du = "r * cos(u) * sin(v)";
    expression->Pz_du = "0";

    expression->Px_dv = "r * cos(u) * cos(v)";
    expression->Py_dv = "r * sin(u) * cos(v)";
    expression->Pz_dv = "r * -sin(v)";

    expression->u_start = "0";
    expression->u_end = "2*pi";

    expression->v_start = "0";
    expression->v_end = "pi";

    expression->u_precision = 50;
    expression->v_precision = 50;

    return expression;
}

std::unique_ptr<ParametricEquationExpressions>
ParametricEquationExpressionsFactory::CreateTorus(){
    auto expression = std::unique_ptr<ParametricEquationExpressions>(
            new ParametricEquationExpressions());
    expression->constants.push_back(
            ParametricEquationConstantExpression{"R",2});
    expression->constants.push_back(
            ParametricEquationConstantExpression{"r",1});

    expression->Px = "(R + r*cos(v)) * cos(u)";
    expression->Py = "(R + r*cos(v)) * sin(u)";
    expression->Pz = "r*sin(v)";

    expression->Px_du = "(R + r*cos(v)) * (-sin(u))";
    expression->Py_du = "(R + r*cos(v)) * cos(u)";
    expression->Pz_du = "0";

    expression->Px_dv = "r*(-sin(v)) * cos(u)";
    expression->Py_dv = "r*(-sin(v)) * sin(u)";
    expression->Pz_dv = "r*cos(v)";

    expression->u_start = "0";
    expression->u_end = "2*pi";

    expression->v_start = "0";
    expression->v_end = "2*pi";

    expression->u_precision = 50;
    expression->v_precision = 50;

    return expression;
}

std::unique_ptr<ParametricEquationExpressions>
ParametricEquationExpressionsFactory::CreateCone(){
    auto expression = std::unique_ptr<ParametricEquationExpressions>(
            new ParametricEquationExpressions());

    expression->Px = "(1.0 - u) / 1.0 * ";
    expression->Py = "(2 + 1*cos(v)) * sin(u)";
    expression->Pz = "1*sin(v)";

    expression->Px_du = "(2 + 1*cos(v)) * (-sin(u))";
    expression->Py_du = "(2 + 1*cos(v)) * cos(u)";
    expression->Pz_du = "0";

    expression->Px_dv = "1*(-sin(v)) * cos(u)";
    expression->Py_dv = "1*(-sin(v)) * sin(u)";
    expression->Pz_dv = "1*cos(v)";

    expression->u_start = "0.0";
    expression->u_end = "1.0";

    expression->v_start = "0";
    expression->v_end = "2*pi";

    expression->u_precision = 50;
    expression->v_precision = 50;

    return expression;
}

std::unique_ptr<ParametricEquationExpressions>
ParametricEquationExpressionsFactory::CreateCylinder(){
    auto expression = std::unique_ptr<ParametricEquationExpressions>(
            new ParametricEquationExpressions());

    expression->Px = "(2 + 1*cos(v)) * cos(u)";
    expression->Py = "(2 + 1*cos(v)) * sin(u)";
    expression->Pz = "1*sin(v)";

    expression->Px_du = "(2 + 1*cos(v)) * (-sin(u))";
    expression->Py_du = "(2 + 1*cos(v)) * cos(u)";
    expression->Pz_du = "0";

    expression->Px_dv = "1*(-sin(v)) * cos(u)";
    expression->Py_dv = "1*(-sin(v)) * sin(u)";
    expression->Pz_dv = "1*cos(v)";

    expression->u_start = "0";
    expression->u_end = "2*pi";

    expression->v_start = "0";
    expression->v_end = "2*pi";

    expression->u_precision = 50;
    expression->v_precision = 50;

    return expression;
}

}