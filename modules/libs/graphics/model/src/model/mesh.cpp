#include "model/mesh.h"

using namespace std;

namespace ifx {

Mesh::Mesh(std::vector<Vertex> vertices,
           vector<GLuint> &indices) :
        vertices_(vertices),
        indices(indices),
        material_(std::make_shared<Material>()),
        primitive_draw_mode_(PrimitiveDrawMode::TRIANGLES),
        polygon_mode_(PolygonMode::FILL){
    computeTangetBasis();
    initBuffers();
}

Mesh::~Mesh() {}

void Mesh::computeTangetBasis() {
    const int DATA_PER_FACE = 3;
    int faceCount = indices.size() / DATA_PER_FACE;
    int vertexIndex = 0;

    for (int i = 0; i < faceCount; i++) {
        if (vertexIndex >= indices.size()) {
            throw new std::invalid_argument("computeTangetBasis out of bounds");
        }
        computeAndStoreTangetBasis(vertices_[indices[vertexIndex + 0]],
                                   vertices_[indices[vertexIndex + 1]],
                                   vertices_[indices[vertexIndex + 2]]);
        vertexIndex += DATA_PER_FACE;

    }
}

/*
void Mesh::computeAndStoreTangetBasis(Vertex& v0, Vertex& v1, Vertex& v2){
    glm::vec3 P = v1.Position - v0.Position;
    glm::vec3 Q = v2.Position - v0.Position;

    float s1 = v1.TexCoords.x - v0.TexCoords.x;
    float t1 = v1.TexCoords.y - v0.TexCoords.y;

    float s2 = v2.TexCoords.x - v0.TexCoords.x;
    float t2 = v2.TexCoords.x - v0.TexCoords.x;

    float tmp = 1.0f;
    float diff = s1*t2 - s2*t1;
    float errTol = 0.0001;
    if(fabsf(diff) >= errTol){
        tmp = 1.0f / diff;
    }
    tmp = 1.0f / diff;
    glm::vec3 tanget = glm::vec3(t2*P.x - t1*Q.x,
                                 t2*P.y - t1*Q.y,
                                 t2*P.z - t1*Q.z);
    tanget *= tmp;

    glm::vec3 binormal = glm::vec3(s1*Q.x - s2*P.x,
                                   s1*Q.y - s2*P.y,
                                   s1*Q.z - s2*P.z);
    binormal *= tmp;

    tanget = glm::normalize(tanget);
    binormal = glm::normalize(binormal);

    glm::vec3 tmpVec = P - Q;
    v0.Tangent = glm::cross(P, v0.Normal);
    v1.Tangent = glm::cross(P, v0.Normal);
    v2.Tangent = glm::cross(P, v0.Normal);

    glm::vec3 test(1.0f, 0.0f, 0.0f);
    glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f),
                                         glm::radians(90.0f),
                                         glm::vec3(0.0f, 1.0f, 0.0f));
    test = glm::vec3(rotateMatrix * glm::vec4(test, 1.0f));
    std::cout << test.x << ", " << test.y << ", " << test.z << std::endl;

    v0.Binormal = binormal;
    v1.Binormal = binormal;
    v2.Binormal = binormal;

}
*/

void Mesh::computeAndStoreTangetBasis(Vertex &v0, Vertex &v1, Vertex &v2) {

    glm::vec2 &uv0 = v0.TexCoords;
    glm::vec2 &uv1 = v1.TexCoords;
    glm::vec2 &uv2 = v2.TexCoords;

    glm::vec3 deltaPos1 = v1.Position - v0.Position;
    glm::vec3 deltaPos2 = v2.Position - v0.Position;

    glm::vec2 deltaUV1 = uv1 - uv0;
    glm::vec2 deltaUV2 = uv2 - uv0;

    float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
    glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
    glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

    tangent = glm::normalize(tangent);
    bitangent = glm::normalize(bitangent);

    v0.Tangent = tangent;
    v1.Tangent = tangent;
    v2.Tangent = tangent;

    v0.Binormal = bitangent;
    v1.Binormal = bitangent;
    v2.Binormal = bitangent;

}

void Mesh::initBuffers() {
    vao_.reset(new VAO());

    vbo_.reset(new VBO(&vertices_));
    ebo_.reset(new EBO(&indices));

    vao_->bindVertexBuffers(*vbo_, *ebo_);
}

void Mesh::bindTextures(const Program &program) {
    BindTexture(material_->diffuse, MATERIAL_DIFFUSE_NAME, program, 0);
    BindTexture(material_->specular, MATERIAL_SPECULAR_NAME, program, 1);
    BindTexture(material_->normal, MATERIAL_NORMAL_NAME, program, 2);
    BindTexture(material_->displacement, MATERIAL_DISPLACEMENT_NAME, program, 3);
    BindTexture(material_->fbo, TEXTURE_SCREEN_NAME, program, 4);
}

void Mesh::BindTexture(std::shared_ptr<Texture2D> texture,
                       std::string program_location,
                       const Program &program, int id){
    if(!texture)
        return;
    int i = id + 31;
    glActiveTexture(GL_TEXTURE31 + id);
    texture->Bind();
    glUniform1i(glGetUniformLocation(program.getID(),
                                     program_location.c_str()), i);
}

void Mesh::bindColor(const Program &program) {
    GLint matShineLoc = glGetUniformLocation(program.getID(),
                                             MATERIAL_SHININESS_NAME.c_str());
    glUniform1f(matShineLoc, material_->shininess);
}

void Mesh::draw(const Program &program) {
    program.use();

    glPolygonMode(GL_FRONT_AND_BACK,
                  PolygonModeToNative(polygon_mode_));

    this->bindTextures(program);
    this->bindColor(program);

    vao_->bind();

    glDrawElements(PrimitiveDrawModeToNative(primitive_draw_mode_),
                   indices.size(), GL_UNSIGNED_INT, 0);

    vao_->unbind();
}

void Mesh::drawInstanced(const Program &program, int count) {
    program.use();

    glPolygonMode(GL_FRONT_AND_BACK,
                  PolygonModeToNative(polygon_mode_));

    this->bindTextures(program);
    this->bindColor(program);

    vao_->bind();

    glDrawElementsInstanced(PrimitiveDrawModeToNative(primitive_draw_mode_),
                            indices.size(),
                            GL_UNSIGNED_INT, 0, count);

    vao_->unbind();
}

std::string Mesh::toString() const {
    string str = "";
    return str;
}

GLenum Mesh::PrimitiveDrawModeToNative(PrimitiveDrawMode mode){
    if(mode == PrimitiveDrawMode::TRIANGLES)
        return GL_TRIANGLES;
    if(mode == PrimitiveDrawMode::PATCHES)
        return GL_PATCHES;
}

GLenum Mesh::PolygonModeToNative(PolygonMode mode){
    if(mode == PolygonMode::FILL)
        return GL_FILL;
    if(mode == PolygonMode::LINES)
        return GL_LINES;
    if(mode == PolygonMode::LINE)
        return GL_LINE;
}

}