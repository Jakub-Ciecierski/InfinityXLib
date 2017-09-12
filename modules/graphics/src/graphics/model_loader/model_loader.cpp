#include "graphics/model_loader/model_loader.h"

#include <graphics/model/model_creator.h>
#include <graphics/shaders/textures/texture_creator.h>

using namespace std;

namespace ifx {

ModelLoader::ModelLoader(std::string filepath,
                         std::shared_ptr<ModelCreator> model_creator,
                         std::shared_ptr<TextureCreator> texture_creator) :
    filepath(filepath),
    model_creator_(model_creator),
    texture_creator_(texture_creator) {}

std::shared_ptr<Model> ModelLoader::loadModel() {
    Assimp::Importer importer;
    const aiScene *scene =
        importer.ReadFile(filepath,
                          aiProcess_Triangulate
                              | aiProcess_FlipUVs
                              | aiProcess_CalcTangentSpace);

    checkError(scene, string(importer.GetErrorString()));

    // Retrieve the directory path of the filepath
    this->directory = filepath.substr(0, filepath.find_last_of('/'));

    std::vector<std::unique_ptr<Mesh>> meshes;
    processNode(scene->mRootNode, scene, meshes);

    auto model = model_creator_->MakeModel(filepath, std::move(meshes));
    printInfo(*model);

    return model;
}

void ModelLoader::checkError(const aiScene *scene,
                             string errorString) {
    if (!scene
        || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        string info = "ERROR::ASSIMP::" + errorString;
        cout << info << endl;
        throw new std::invalid_argument(info);
    }
}

void ModelLoader::processNode(aiNode *node, const aiScene *scene,
                              vector<std::unique_ptr<Mesh>> &meshes) {
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        std::unique_ptr<Mesh> ifxMesh =
            std::move(this->processMesh(mesh, scene));

        meshes.push_back(std::move(ifxMesh));
    }
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, meshes);
    }
}

std::unique_ptr<Mesh> ModelLoader::processMesh(aiMesh *mesh,
                                               const aiScene *scene) {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture2D>> textures;

    vertices = processVertices(mesh);
    indices = processIndices(mesh);
    textures = processTextures(mesh, scene);
    if (!mesh->HasTangentsAndBitangents())
        calculateTBN(vertices, indices);

    auto mesh_ifx = std::unique_ptr<Mesh>(new Mesh(vertices, indices));
    auto material = std::make_shared<Material>();
    for (unsigned int i = 0; i < textures.size(); i++)
        material->AddTexture(textures[i]);
    mesh_ifx->material(material);

    return mesh_ifx;
}

vector<Vertex> ModelLoader::processVertices(aiMesh *mesh) {
    vector<Vertex> vertices;
    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        glm::vec3 vPos;
        vPos.x = mesh->mVertices[i].x;
        vPos.y = mesh->mVertices[i].y;
        vPos.z = mesh->mVertices[i].z;
        vertex.Position = vPos;

        glm::vec3 vNorm;
        if (mesh->mNormals != nullptr) {
            vNorm.x = mesh->mNormals[i].x;
            vNorm.y = mesh->mNormals[i].y;
            vNorm.z = mesh->mNormals[i].z;
        } else {
            std::cout << "No normals" << std::endl;
        }
        vertex.Normal = vNorm;

        if (mesh->HasTangentsAndBitangents()) {
            vertex.Tangent.x = mesh->mTangents[i].x;
            vertex.Tangent.y = mesh->mTangents[i].y;
            vertex.Tangent.z = mesh->mTangents[i].z;

            vertex.Binormal.x = mesh->mBitangents[i].x;
            vertex.Binormal.y = mesh->mBitangents[i].y;
            vertex.Binormal.z = mesh->mBitangents[i].z;
        }

        // Assimp has up to 8 different textureCoords, we only care about one
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vTex;
            vTex.x = mesh->mTextureCoords[0][i].x;
            vTex.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vTex;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    return vertices;
}

vector<GLuint> ModelLoader::processIndices(aiMesh *mesh) {
    vector<GLuint> indices;

    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    return indices;
}

void ModelLoader::calculateTBN(std::vector<Vertex> &vertices,
                               const std::vector<GLuint> &indices) {
    std::cout << "Calculating Tangents And Bitangents" << std::endl;
    const int DATA_PER_FACE = 3;
    int faceCount = indices.size() / DATA_PER_FACE;
    unsigned int vertexIndex = 0;

    for (int i = 0; i < faceCount; i++) {
        if (vertexIndex >= indices.size()) {
            throw new std::invalid_argument("computeTangetBasis out of bounds");
        }
        calculateTBN(vertices[indices[vertexIndex + 0]],
                     vertices[indices[vertexIndex + 1]],
                     vertices[indices[vertexIndex + 2]]);
        vertexIndex += DATA_PER_FACE;
    }
}

void ModelLoader::calculateTBN(Vertex & v0, Vertex & v1, Vertex & v2) {
    glm::vec2 &uv0 = v0.TexCoords;
    glm::vec2 &uv1 = v1.TexCoords;
    glm::vec2 &uv2 = v2.TexCoords;

    glm::vec3 edge1 = v1.Position - v0.Position;
    glm::vec3 edge2 = v2.Position - v0.Position;

    glm::vec2 deltaUV1 = uv1 - uv0;
    glm::vec2 deltaUV2 = uv2 - uv0;

    float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
    glm::vec3 tangent;
    tangent.x = (edge1.x * deltaUV2.y - edge2.x * deltaUV1.y) * r;
    tangent.y = (edge1.y * deltaUV2.y - edge2.y * deltaUV1.y) * r;
    tangent.z = (edge1.z * deltaUV2.y - edge2.z * deltaUV1.y) * r;

    glm::vec3 bitangent;
    bitangent.x = (edge2.x * deltaUV1.x - edge1.x * deltaUV2.x) * r;
    bitangent.y = (edge2.y * deltaUV1.x - edge1.y * deltaUV2.x) * r;
    bitangent.z = (edge2.z * deltaUV1.x - edge1.z * deltaUV2.x) * r;

    tangent = glm::normalize(tangent);
    bitangent = glm::normalize(bitangent);

    v0.Tangent = tangent;
    v1.Tangent = tangent;
    v2.Tangent = tangent;

    v0.Binormal = bitangent;
    v1.Binormal = bitangent;
    v2.Binormal = bitangent;
}

std::vector<std::shared_ptr<Texture2D>> ModelLoader::processTextures(
    aiMesh *mesh, const aiScene *scene) {
    std::vector<std::shared_ptr<Texture2D>> textures;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture2D>> diffuseMaps
            = loadMaterialTextures(material, aiTextureType_DIFFUSE,
                                   TextureTypes::DIFFUSE);
        std::vector<std::shared_ptr<Texture2D>> specularMaps
            = loadMaterialTextures(material, aiTextureType_SPECULAR,
                                   TextureTypes::SPECULAR);
        // WARNING aiTextureType_HEIGHT hide the Normal maps !!
        // For .obj format the normal map is under aiTextureType_HEIGHT.
        // TODO check the format.
        std::vector<std::shared_ptr<Texture2D>> normalMaps
            = loadMaterialTextures(material, aiTextureType_HEIGHT,
                                   TextureTypes::NORMAL);

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(),
                        specularMaps.end());
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    }
    return textures;
}

std::vector<std::shared_ptr<Texture2D>> ModelLoader::loadMaterialTextures(
    aiMaterial *mat, aiTextureType type, TextureTypes texType) {
    std::vector<std::shared_ptr<Texture2D>> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        string filename = string(str.C_Str());

        std::string filepath = directory + '/' + filename;
        auto texture
            = texture_creator_->MakeTexture2DFromFile(filepath, texType);
        textures.push_back(texture);
    }
    return textures;
}

void ModelLoader::printInfo(const Model &model) {
    std::cout << model.toString() << std::endl;
}
}
