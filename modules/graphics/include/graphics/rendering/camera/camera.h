#ifndef DUCK_CAMERA_H
#define DUCK_CAMERA_H

#include <graphics/shaders/program.h>
#include <math/math_ifx.h>
#include <math/transform.h>

#include <memory>

namespace ifx {


/*
 * Camera represents the Projection and View Matrices.
 * Uses Euler angles (lookAt) FPS style.
 */
class Camera : public Transformable{
public:
    Camera(int *width, int *height,
           float FOV = 45.0f,
           float near = 0.01f, float far = 100.0f);

    ~Camera();

    /**
     * Override from MovableObject.
     */
    void rotate(const glm::vec3 &rotation) override;
    void rotateTo(const glm::vec3 &rotation) override;

    /**
     * Override from Transformable.
     */
    virtual void Update(float time_delta = 0) override;

    void moveForward(float speedBoost);
    void moveBackward(float speedBoost);
    void moveLeft(float speedBoost);
    void moveRight(float speedBoost);
    void moveUp(float speedBoost);
    void moveDown(float speedBoost);

    void use(const Program &program);

    const glm::mat4 &getViewMatrix();
    const glm::mat4 &getProjectionMatrix();

    const glm::vec3& GetRight(){return right;}
    const glm::vec3& GetUp(){return up;}
private:
    void clampRotation();

    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 WorldUp;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    int *width;
    int *height;

    float FOV;

    float near;
    float far;

    float last_mouse_x;
    float last_mouse_y;
};
}

#endif //DUCK_CAMERA_H

