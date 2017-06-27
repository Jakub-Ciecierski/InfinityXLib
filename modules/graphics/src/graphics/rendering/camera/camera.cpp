#include "graphics/rendering/camera/camera.h"

#include "graphics/shaders/data/shader_data.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

namespace ifx {

Camera::Camera(int *width, int *height,
               float FOV, float near, float far) :
        width(width), height(height),
        FOV(FOV), near(near), far(far) {
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    moveTo(glm::vec3(1,1,1));
    Update();
}

Camera::~Camera() {}


void Camera::rotate(const glm::vec3 &rotation) {
    Transformable::rotate(rotation);

    //clampRotation();
}

void Camera::rotateTo(const glm::vec3 &rotation) {
    Transformable::rotateTo(rotation);

    //clampRotation();
}

void Camera::Update(float time_delta) {
    UpdateGlobal();

    ProjectionMatrix
            = glm::perspective(FOV, (float) (*width) / (float) (*height),
                               near, far);
    auto position = getPosition();
    auto rotation = getRotation();

    glm::vec3 direction;
    direction.x = cos(glm::radians(rotation.x))
                  * cos(glm::radians(rotation.y));
    direction.y = sin(glm::radians(rotation.y));
    direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    direction = glm::normalize(direction);
    SetDirection(direction);

    right = glm::normalize(glm::cross(direction, this->WorldUp));
    up = glm::normalize(glm::cross(right, direction));

    ViewMatrix = glm::lookAt(position, position + direction, up);
}

void Camera::moveForward(float speedBoost) {
    move(getDirection() * speedBoost);
}

void Camera::moveBackward(float speedBoost) {
    move(-getDirection() * speedBoost);
}

void Camera::moveLeft(float speedBoost) {
    move(-right * speedBoost);
}

void Camera::moveRight(float speedBoost) {
    move(right * speedBoost);
}

void Camera::moveUp(float speedBoost) {
    move(up * speedBoost);
}

void Camera::moveDown(float speedBoost) {
    move(-up * speedBoost);
}

void Camera::use(const Program &program) {
    program.use();

    // View Matrix
    GLint viewLoc = glGetUniformLocation(program.getID(),
                                         VIEW_MATRIX_NAME.c_str());
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(getViewMatrix()));

    // Projection Matrix
    GLint projLoc = glGetUniformLocation(program.getID(),
                                         PROJECTION_MATRIX_NAME.c_str());
    glUniformMatrix4fv(projLoc, 1, GL_FALSE,
                       glm::value_ptr(getProjectionMatrix()));

    // View Position
    GLint viewPosLoc = glGetUniformLocation(program.getID(),
                                            VIEW_POSITION_NAME.c_str());
    auto& position = getPosition();
    glUniform3f(viewPosLoc, position.x, position.y, position.z);
}

const glm::mat4 &Camera::getViewMatrix() {
    return this->ViewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix() {
    return this->ProjectionMatrix;
}

void Camera::clampRotation() {
    glm::vec3 rotation = getRotation();
    if (rotation.y < -89) {
        rotation.y = -89;
    }
    if (rotation.y > 89) {
        rotation.y = 89;
    }
    Transformable::rotateTo(rotation);
}

}