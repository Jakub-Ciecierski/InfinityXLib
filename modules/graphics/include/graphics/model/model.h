#ifndef DUCK_MODEL_H
#define DUCK_MODEL_H

#include "graphics/model/mesh.h"
#include <resources/resource.h>

#include <memory>
#include <ostream>

namespace ifx {

/*
 * Model class is an encapsulation of many meshes take up a single model
 */
class Model : public ifx::Resource {
public:
    ~Model() = default;

    std::vector<Mesh *> getMeshes();

    Mesh *getMesh(int i);

    void draw(const Program &program);

    void drawInstanced(const Program &program, int count);

    std::string toString() const;

    void AddMesh(std::unique_ptr<Mesh> mesh);

    friend class ModelCreator;
private:
    Model(std::string filepath,
          std::vector<std::unique_ptr<Mesh>> meshes);

    std::vector<std::unique_ptr<Mesh>> meshes;

};
}

#endif //DUCK_MODEL_H
