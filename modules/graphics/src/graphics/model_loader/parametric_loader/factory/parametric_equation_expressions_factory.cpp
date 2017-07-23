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
            ParametricEquationConstantExpression{"c",2});
    expression->constants.push_back(
            ParametricEquationConstantExpression{"a",1});

    expression->Px = "(c + a*cos(v)) * cos(u)";
    expression->Py = "(c + a*cos(v)) * sin(u)";
    expression->Pz = "a*sin(v)";

    expression->Px_du = "(c + a*cos(v)) * (-sin(u))";
    expression->Py_du = "(c + a*cos(v)) * cos(u)";
    expression->Pz_du = "0";

    expression->Px_dv = "a*(-sin(v)) * cos(u)";
    expression->Py_dv = "a*(-sin(v)) * sin(u)";
    expression->Pz_dv = "a*cos(v)";

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
    expression->constants.push_back(
            ParametricEquationConstantExpression{"h",2});
    expression->constants.push_back(
            ParametricEquationConstantExpression{"r",1});

    expression->Px = "((h - u) / h) * r * cos(v)";
    expression->Py = "((h - u) / h) * r * sin(v)";
    expression->Pz = "u";

    expression->Px_du = "(-r*cos(v)) / h";
    expression->Py_du = "((-u + h) * r * sin(v)) / h";
    expression->Pz_du = "1";

    expression->Px_dv = "(-r * sin(v)) / h";
    expression->Py_dv = "((-u+h)*r*cos(v)) / h";
    expression->Pz_dv = "0";

    expression->u_start = "0.0";
    expression->u_end = "h";

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
    expression->constants.push_back(
            ParametricEquationConstantExpression{"h",2});
    expression->constants.push_back(
            ParametricEquationConstantExpression{"r",1});

    expression->Px = "r*cos(u)";
    expression->Py = "r*sin(u)";
    expression->Pz = "v";

    expression->Px_du = "-r*sin(u)";
    expression->Py_du = "r*cos(u)";
    expression->Pz_du = "0";

    expression->Px_dv = "0";
    expression->Py_dv = "0";
    expression->Pz_dv = "1";

    expression->u_start = "0";
    expression->u_end = "2*pi";

    expression->v_start = "0";
    expression->v_end = "h";

    expression->u_precision = 50;
    expression->v_precision = 50;

    return expression;
}

}