#ifndef PROJECT_PARAMETRIC_INTERPRETER_H
#define PROJECT_PARAMETRIC_INTERPRETER_H

#include <string>
#include <memory>
#include <vector>

namespace exprtk{

template <typename T>
class expression;

template <typename T>
class symbol_table;
}

namespace ifx {

struct ParametricEquation;

struct ParametricEquationConstantExpression{
    std::string name;
    float value;
};

struct ParametricEquationExpressions{
    std::string Px;
    std::string Py;
    std::string Pz;

    std::string Px_du;
    std::string Py_du;
    std::string Pz_du;

    std::string Px_dv;
    std::string Py_dv;
    std::string Pz_dv;

    std::string u_start;
    std::string u_end;

    std::string v_start;
    std::string v_end;

    std::vector<ParametricEquationConstantExpression> constants;

    int u_precision;
    int v_precision;
};

/**
 * Interprets parametric equations and inputs them to ModelParametricLoader
 */
class ParametricInterpreter {
public:

    ParametricInterpreter() = default;
    ~ParametricInterpreter() = default;

    std::unique_ptr<ParametricEquation> Interpret(
            const ParametricEquationExpressions& expression);

private:
    exprtk::symbol_table<double> CreateSymbolTable(
            const ParametricEquationExpressions &expressions,
            ParametricEquation& parametric_equation);

    void AddEquation(
            const ParametricEquationExpressions &expressions,
            ParametricEquation &parametric_equation,
            exprtk::symbol_table<double> &exprtk_symbol_table);
    void AddEquationDu(
            const ParametricEquationExpressions &expressions,
            ParametricEquation &parametric_equation,
            exprtk::symbol_table<double> &exprtk_symbol_table);
    void AddEquationDv(
            const ParametricEquationExpressions &expressions,
            ParametricEquation &parametric_equation,
            exprtk::symbol_table<double> &exprtk_symbol_table);
    void AddVariables(
            const ParametricEquationExpressions &expressions,
            ParametricEquation &parametric_equation,
            exprtk::symbol_table<double> &exprtk_symbol_table);
    void AddVariablesPrecision(
            const ParametricEquationExpressions &expressions,
            ParametricEquation &parametric_equation);

    exprtk::expression<double> CreateExpression(
            exprtk::symbol_table<double> &exprtk_symbol_table,
            std::string expression);
};
}


#endif //PROJECT_PARAMETRIC_INTERPRETER_H
