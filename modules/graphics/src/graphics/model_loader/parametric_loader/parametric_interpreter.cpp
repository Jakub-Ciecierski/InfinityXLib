#include "graphics/model_loader/parametric_loader/parametric_interpreter.h"

#include "graphics/model_loader/parametric_loader/model_parametric_loader.h"

#include <exprtk.hpp>

namespace ifx {

std::unique_ptr<ParametricEquation> ParametricInterpreter::Interpret(
    const ParametricEquationExpressions &expressions) {
    auto parametric_equation = std::unique_ptr<ParametricEquation>(
        new ParametricEquation());

    auto exprtk_symbol_table = CreateSymbolTable(expressions,
                                                 *parametric_equation);

    AddEquation(expressions, *parametric_equation.get(), exprtk_symbol_table);
    AddEquationDu(expressions, *parametric_equation.get(), exprtk_symbol_table);
    AddEquationDv(expressions, *parametric_equation.get(), exprtk_symbol_table);
    AddVariables(expressions, *parametric_equation.get(), exprtk_symbol_table);
    AddVariablesPrecision(expressions, *parametric_equation.get());

    return parametric_equation;
}

exprtk::symbol_table<double> ParametricInterpreter::CreateSymbolTable(
    const ParametricEquationExpressions &expressions,
    ParametricEquation &parametric_equation) {
    exprtk::symbol_table<double> exprtk_symbol_table;
    for (auto &constant : expressions.constants) {
        if (!exprtk_symbol_table.add_constant(constant.name, constant.value)) {
            throw std::invalid_argument(
                "Multiple constants with the same name. "
                    "Not Case Sensitive");
        }
    }
    exprtk_symbol_table.add_constants();

    exprtk_symbol_table.add_variable("u", parametric_equation.u_global);
    exprtk_symbol_table.add_variable("v", parametric_equation.v_global);

    return exprtk_symbol_table;
}

void ParametricInterpreter::AddEquation(
    const ParametricEquationExpressions &expressions,
    ParametricEquation &parametric_equation,
    exprtk::symbol_table<double> &exprtk_symbol_table) {
    auto exprtk_expression_Px = CreateExpression(exprtk_symbol_table,
                                                 expressions.Px);
    auto exprtk_expression_Py = CreateExpression(exprtk_symbol_table,
                                                 expressions.Py);
    auto exprtk_expression_Pz = CreateExpression(exprtk_symbol_table,
                                                 expressions.Pz);
    parametric_equation.P = [
        &parametric_equation,
        exprtk_expression_Px,
        exprtk_expression_Py,
        exprtk_expression_Pz](double u, double v) -> glm::vec3 {
        parametric_equation.u_global = u;
        parametric_equation.v_global = v;
        return glm::vec3(
            exprtk_expression_Px.value(),
            exprtk_expression_Py.value(),
            exprtk_expression_Pz.value()
        );
    };
}

void ParametricInterpreter::AddEquationDu(
    const ParametricEquationExpressions &expressions,
    ParametricEquation &parametric_equation,
    exprtk::symbol_table<double> &exprtk_symbol_table) {
    auto exprtk_expression_Px_du = CreateExpression(exprtk_symbol_table,
                                                    expressions.Px_du);
    auto exprtk_expression_Py_du = CreateExpression(exprtk_symbol_table,
                                                    expressions.Py_du);
    auto exprtk_expression_Pz_du = CreateExpression(exprtk_symbol_table,
                                                    expressions.Pz_du);

    parametric_equation.Pu = [
        &parametric_equation,
        exprtk_expression_Px_du,
        exprtk_expression_Py_du,
        exprtk_expression_Pz_du](double u, double v) -> glm::vec3 {
        parametric_equation.u_global = u;
        parametric_equation.v_global = v;
        return glm::vec3(
            exprtk_expression_Px_du.value(),
            exprtk_expression_Py_du.value(),
            exprtk_expression_Pz_du.value()
        );
    };
}

void ParametricInterpreter::AddEquationDv(
    const ParametricEquationExpressions &expressions,
    ParametricEquation &parametric_equation,
    exprtk::symbol_table<double> &exprtk_symbol_table) {
    auto exprtk_expression_Px_dv = CreateExpression(exprtk_symbol_table,
                                                    expressions.Px_dv);
    auto exprtk_expression_Py_dv = CreateExpression(exprtk_symbol_table,
                                                    expressions.Py_dv);
    auto exprtk_expression_Pz_dv = CreateExpression(exprtk_symbol_table,
                                                    expressions.Pz_dv);

    parametric_equation.Pv = [
        &parametric_equation,
        exprtk_expression_Px_dv,
        exprtk_expression_Py_dv,
        exprtk_expression_Pz_dv](double u, double v) -> glm::vec3 {
        parametric_equation.u_global = u;
        parametric_equation.v_global = v;
        return glm::vec3(
            exprtk_expression_Px_dv.value(),
            exprtk_expression_Py_dv.value(),
            exprtk_expression_Pz_dv.value()
        );
    };
}

void ParametricInterpreter::AddVariables(
    const ParametricEquationExpressions &expressions,
    ParametricEquation &parametric_equation,
    exprtk::symbol_table<double> &exprtk_symbol_table) {
    auto exprtk_expression_u_start = CreateExpression(exprtk_symbol_table,
                                                      expressions.u_start);
    auto exprtk_expression_u_end = CreateExpression(exprtk_symbol_table,
                                                    expressions.u_end);
    auto exprtk_expression_v_start = CreateExpression(exprtk_symbol_table,
                                                      expressions.v_start);
    auto exprtk_expression_v_end = CreateExpression(exprtk_symbol_table,
                                                    expressions.v_end);

    parametric_equation.u_start = exprtk_expression_u_start.value();
    parametric_equation.u_end = exprtk_expression_u_end.value();

    parametric_equation.v_start = exprtk_expression_v_start.value();
    parametric_equation.v_end = exprtk_expression_v_end.value();
}

void ParametricInterpreter::AddVariablesPrecision(
    const ParametricEquationExpressions &expressions,
    ParametricEquation &parametric_equation) {
    parametric_equation.u_precision = expressions.u_precision;
    parametric_equation.v_precision = expressions.v_precision;
}

exprtk::expression<double> ParametricInterpreter::CreateExpression(
    exprtk::symbol_table<double> &exprtk_symbol_table,
    std::string expression) {
    exprtk::expression<double> exprtk_expression;
    exprtk_expression.register_symbol_table(exprtk_symbol_table);
    exprtk::parser<double> exprtk_parser;
    auto is_compiled = exprtk_parser.compile(expression, exprtk_expression);

    if (!is_compiled)
        throw std::invalid_argument(
            "Invalid Syntax. Variables must be named: (u,v)");

    return exprtk_expression;
}

}