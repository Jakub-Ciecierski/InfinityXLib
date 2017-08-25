#ifndef DUCK_CAMERA_H
#define DUCK_CAMERA_H

#include <graphics/shaders/program.h>
#include <math/math_ifx.h>
#include <math/transform.h>

#include <memory>

namespace ifx {

enum class CameraStyle{
    FPS, ThirdPerson
};

/*
 * Camera represents the Projection and View Matrices.
 * Uses Euler angles (lookAt) FPS style.
 */
class Camera : public Transformable{
public:
    Camera(int *width, int *height,
           float FOV = 45.0f,
           float near = 0.01f, float far = 100.0f);

    virtual ~Camera() = default;

    float near_plane(){return near_;}
    void near_plane(float near){near_ = near;}

    float far_plane(){return far_;}
    void far_plane(float far){far_ = far;}

    CameraStyle camera_style(){return camera_style_;}
    void camera_style(CameraStyle camera_style){camera_style_ = camera_style;}

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

    glm::mat4 ComputeViewMatrix(const glm::vec3 position,
                                const glm::vec3 direction,
                                const glm::vec3 up);

    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 WorldUp;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    int *width;
    int *height;

    float FOV;

    float near_;
    float far_;

    CameraStyle camera_style_;
};
}

#endif //DUCK_CAMERA_H

