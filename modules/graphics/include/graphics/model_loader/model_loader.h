#ifndef DUCK_MODEL_LOADER_H
#define DUCK_MODEL_LOADER_H

#include <graphics/model/model.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <graphics/shaders/textures/texture.h>

#include <memory>

namespace ifx {

class ModelCreator;
class TextureCreator;

/*
 * Loads Models using Assimp.
 * Loaded Models are stored in cache memory.
 * The Mesh Material shininess is not provided !
 */
class ModelLoader {
public:

    ModelLoader(
            std::string filepath,
            std::shared_ptr<ModelCreator> model_creator,
            std::shared_ptr<TextureCreator> texture_creator);

    ~ModelLoader();

    std::shared_ptr<ifx::Model> loadModel();

private:
    void checkError(const aiScene *scene,
                    std::string errorString);

    /*
     * Processes each assimp Node recursively
     */
    void processNode(aiNode *node, const aiScene *scene,
                     std::vector<std::unique_ptr<Mesh>> &meshes);

    /*
     * Translates the Assimp::Mesh into ifx::Mesh
     */
    std::unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);

    /*
     * Loads all vertices
     */
    std::vector<Vertex> processVertices(aiMesh *mesh);

    /*
     * Loads all indices
     */
    std::vector<GLuint> processIndices(aiMesh *mesh);

    void calculateTBN(std::vector<Vertex>& vertices,
                      const std::vector<GLuint>& indices);
    void calculateTBN(Vertex& v0, Vertex& v1, Vertex& v2);

    /*
     * Loads all textures.
     * Uses loadMaterialTextures to load all textures of specific type.
     * Update this function to support more textures types.
     */
    std::vector<std::shared_ptr<Texture2D>> processTextures(
            aiMesh *mesh, const aiScene* scene);

    /*
     * Loads all texture of specific type e.g. Diffuse or Specular
     */
    std::vector<std::shared_ptr<Texture2D>> loadMaterialTextures(
            aiMaterial *mat,
            aiTextureType type,
            TextureTypes texType);

    void printInfo(const Model &model);

    std::string filepath;
    std::string directory;

    std::shared_ptr<ModelCreator> model_creator_;
    std::shared_ptr<TextureCreator> texture_creator_;
};
}

#endif //DUCK_MODEL_LOADER_H