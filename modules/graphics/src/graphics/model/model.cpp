#include "graphics/model/model.h"

#include <resources/resource_memory_cache.h>

using namespace std;

namespace ifx {

Model::Model(std::string filepath,
             std::vector<std::unique_ptr<Mesh>> meshes) :
    ifx::Resource(filepath, ifx::ResourceType::MODEL),
    meshes(std::move(meshes)) {}

std::vector<Mesh *> Model::getMeshes() {
    std::vector<Mesh *> meshes_raw(meshes.size());
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes_raw[i] = meshes[i].get();
    return meshes_raw;
}

Mesh *Model::getMesh(int i) {
    return meshes[i].get();
}

void Model::draw(const Program &program) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i]->draw(program);
    }
}

void Model::drawInstanced(const Program &program, int count) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i]->drawInstanced(program, count);
    }
}

std::string Model::toString() const {
    std::string str = "";
    str += "Mesh count:  " + std::to_string(meshes.size()) + "\n";
    for (unsigned int i = 0; i < meshes.size(); i++) {
        str += "Mesh[" + std::to_string(i) + "]" + "\n";
        str += meshes[i]->toString();
    }

    return str;
}
}