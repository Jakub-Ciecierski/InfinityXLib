#include "graphics/model_loader/parametric_loader/model_parametric_loader.h"

#include <graphics/model/mesh.h>
#include <factory/mesh_factory.h>
#include <graphics/model/model_creator.h>

namespace ifx{

ModelParametricLoader::ModelParametricLoader(){}
ModelParametricLoader::~ModelParametricLoader(){}

std::shared_ptr<Model> ModelParametricLoader::CreateModel(
        const ParametricEquation& parametric_equation,
        std::shared_ptr<ModelCreator> model_creator) {
    std::vector<Vertex> vertices = CreateVertices(parametric_equation);
    std::vector<GLuint> indices = CreateIndices(parametric_equation);

    auto mesh = std::unique_ptr<Mesh>(new Mesh(vertices, indices));

    return model_creator->MakeModel(ifx::NO_FILEPATH, std::move(mesh));
}

std::vector<Vertex> ModelParametricLoader::CreateVertices(const ParametricEquation& parametric_equation){
    std::vector<Vertex> vertices;

    for(double i = 0; i <= parametric_equation.u_precision; i++){
        auto u = ((i / parametric_equation.u_precision) * parametric_equation.u_end) + parametric_equation.u_start;
        for(double j = 0; j <= parametric_equation.v_precision; j++){
            auto v = ((j / (double)parametric_equation.v_precision) *
                    parametric_equation.v_end) + parametric_equation.v_start;
            Vertex vs;
            vs.Position = parametric_equation.P(u, v);
            vs.Normal = -glm::cross(parametric_equation.Pu(u, v),
                                    parametric_equation.Pv(u, v));
            vs.TexCoords = glm::vec2(1 - (j / (double)parametric_equation.v_precision),
                                     1 - (i / (double)parametric_equation.u_precision));

            vertices.push_back(vs);
        }
    }
    return vertices;
}

std::vector<unsigned int> ModelParametricLoader::CreateIndices(const ParametricEquation& parametric_equation){
    std::vector<GLuint> indices;

    for(double i = 0; i < parametric_equation.u_precision; i++){
        for(double j = 0; j < parametric_equation.v_precision; j++){
            unsigned int first = (i * ((double)parametric_equation.v_precision + 1)) + j;
            unsigned int second = first + (double)parametric_equation.v_precision + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return indices;
}

/*
    ParametricEquation parametric_equation {
            [](double u, double v) -> glm::vec3 {
                return glm::vec3(cos(u) * sin(v),
                                 sin(u) * sin(v),
                                 cos(v));
            },

            [](double u, double v) -> glm::vec3 {
                return glm::vec3(-sin(u)*sin(v),
                                 cos(u)*sin(v),
                                 0);
            },

            [](double u, double v) -> glm::vec3 {
                return glm::vec3(cos(u)*cos(v),
                                 sin(u)*cos(v),
                                 -sin(v));
            },
            0, 2*M_PI,
            0, M_PI,
            20, 20
    };
*/
/*
    ParametricEquation parametric_equation {
            [](double u, double v) -> glm::vec3 {
                auto c = 2;
                auto a = 1;
                return glm::vec3((c + a * cos(v)) * cos(u),
                                 (c + a * cos(v)) * sin(u),
                                 a * sin(v));
            },

            [](double u, double v) -> glm::vec3 {
                return glm::vec3(-sin(u)*sin(v),
                                 cos(u)*sin(v),
                                 0);
            },

            [](double u, double v) -> glm::vec3 {
                return glm::vec3(cos(u)*cos(v),
                                 sin(u)*cos(v),
                                 -sin(v));
            },
            0, 2*M_PI,
            0, 2*M_PI,
            50, 50
    };
*/


}
