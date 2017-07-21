#ifndef PROJECT_MODEL_PARAMETRIC_LOADER_H
#define PROJECT_MODEL_PARAMETRIC_LOADER_H

#include <math/math_ifx.h>
#include <functional>

#include <memory>

class Vertex;

namespace ifx {

class Model;
class ModelCreator;

struct ParametricEquation{
    std::function<glm::vec3(double u, double v)> P;
    std::function<glm::vec3(double u, double v)> Pu;
    std::function<glm::vec3(double u, double v)> Pv;

    double u_start;
    double u_end;

    double v_start;
    double v_end;

    double u_precision;
    double v_precision;
};


class ModelParametricLoader {
public:
    ModelParametricLoader();
    ~ModelParametricLoader();

    std::shared_ptr<Model> CreateModel(const ParametricEquation &parametric_equation,
                                       std::shared_ptr<ModelCreator> model_creator);
private:
    std::vector<Vertex> CreateVertices(const ParametricEquation& parametric_equation);

    std::vector<unsigned int> CreateIndices(const ParametricEquation& parametric_equation);
};

}
#endif //PROJECT_MODEL_PARAMETRIC_LOADER_H
