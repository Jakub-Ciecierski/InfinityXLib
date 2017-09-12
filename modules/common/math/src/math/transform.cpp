#include "math/transform.h"

namespace ifx {

Transformable::Transformable() :
    parent_object_(nullptr) {
    initVectors();
}

void Transformable::Update(float time_delta) {
    UpdateGlobal();

    auto &global_position = global_transform_.position;
    auto &global_rotation = global_transform_.rotation;
    auto &global_scale = global_transform_.scale;

    ModelMatrix = glm::mat4(1.0f);

    TranslateMatrix = translate(glm::mat4(1.0f), global_position);

    glm::mat4 RotateX = glm::rotate(glm::mat4(1.0f),
                                    glm::radians(global_rotation.x),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 RotateY = glm::rotate(glm::mat4(1.0f),
                                    glm::radians(global_rotation.y),
                                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 RotateZ = glm::rotate(glm::mat4(1.0f),
                                    glm::radians(global_rotation.z),
                                    glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), global_scale);

    RotationMatrix = RotateZ * RotateY * RotateX;

    ModelMatrix = TranslateMatrix * RotationMatrix * Scale;

    direction.x = cos(glm::radians(global_rotation.x))
        * cos(glm::radians(global_rotation.y));
    direction.y = sin(glm::radians(global_rotation.y));
    direction.z = sin(glm::radians(global_rotation.x))
        * cos(glm::radians(global_rotation.y));
    direction = glm::normalize(direction);
}

void Transformable::UpdateGlobal() {
    glm::vec3 parent_position = glm::vec3(0, 0, 0);
    glm::vec3 parent_rotation = glm::vec3(0, 0, 0);
    glm::vec3 parent_scale = glm::vec3(1, 1, 1);

    if (parent_object_) {
        auto &parent_global = parent_object_->global_transform();
        parent_position = parent_global.position;
        parent_rotation = parent_global.rotation;
        parent_scale = parent_global.scale;
    }

    global_transform_.position = local_transform_.position + parent_position;
    global_transform_.rotation = local_transform_.rotation + parent_rotation;
    global_transform_.scale = local_transform_.scale * parent_scale;
}

void Transformable::moveTo(const glm::vec3 &position) {
    local_transform_.position = position;
}

void Transformable::move(const glm::vec3 &position) {
    local_transform_.position += position;
}

void Transformable::rotateTo(const glm::vec3 &rotate) {
    local_transform_.rotation = rotate;
}

void Transformable::rotate(const glm::vec3 &rotate) {
    local_transform_.rotation += rotate;
}

void Transformable::scale(float scale) {
    local_transform_.scale = glm::vec3(scale, scale, scale);
}

void Transformable::scale(const glm::vec3 &scale) {
    local_transform_.scale = scale;
}

void Transformable::LookAt(const glm::vec3 &v) {
    look_at_ = v;
}

const glm::vec3 &Transformable::getPosition() {
    UpdateGlobal();
    return global_transform_.position;
}

const glm::vec3 &Transformable::getRotation() {
    UpdateGlobal();
    return global_transform_.rotation;
}

const glm::vec3 &Transformable::getScale() {
    UpdateGlobal();
    return global_transform_.scale;
}

const glm::vec3 &Transformable::getDirection() {
    return this->direction;
}

const glm::mat4 &Transformable::GetModelMatrix() {
    return ModelMatrix;
}

const glm::mat4 &Transformable::GetTranslateMatrix() {
    return TranslateMatrix;
}

const glm::mat4 &Transformable::GetRotationMatrix() {
    return RotationMatrix;
}

void Transformable::initVectors() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    look_at_ = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Transformable::SetDirection(const glm::vec3 &dir) {
    direction = dir;
}

void Transformable::SetParent(Transformable *parent_object) {
    parent_object_ = parent_object;
}

} // ifx