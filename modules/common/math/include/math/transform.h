#ifndef PROJECT_TRANSFORM_H
#define PROJECT_TRANSFORM_H

#include <math/math_ifx.h>

#include <memory>

namespace ifx {

struct TransformData {
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 rotation = glm::vec3(0,0,0);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

class Transformable {
public:
    Transformable();

    ~Transformable();

    const glm::vec3& look_at(){return look_at_;}
    const TransformData& local_transform() {return local_transform_;}
    const TransformData& global_transform() {
        UpdateGlobal();
        return global_transform_;
    }
    void local_transform(TransformData data) {
        local_transform_ = data;
        UpdateGlobal();
    }
    void global_transform(TransformData data) {
        global_transform_ = data;
    }
    Transformable* movable_parent(){return parent_object_;}

    virtual void update();

    /*
     * Moves to position
     */
    void moveTo(const glm::vec3 &position);

    /*
     * Moves by the position vector.
     * The position is added to current on
     */
    void move(const glm::vec3 &position);

    /*
     * Rotates to given rotation vector
     */
    virtual void rotateTo(const glm::vec3 &rotate);

    /*
     * Rotates by the rotation vector.
     * The values are added to current one
     */
    virtual void rotate(const glm::vec3 &rotate);

    void scale(float scale);
    void scale(const glm::vec3 &scale);

    void LookAt(const glm::vec3& v);

    const glm::vec3& getPosition();
    const glm::vec3& getRotation();
    const glm::vec3& getScale();

    const glm::vec3& getDirection();

    const glm::mat4& GetModelMatrix();
    const glm::mat4& GetTranslateMatrix();
    const glm::mat4& GetRotationMatrix();

    void SetParent(Transformable* parent_object);

protected:
    void UpdateGlobal();
    void SetDirection(const glm::vec3& dir);

private:
    void initVectors();

    TransformData local_transform_;
    // Global is used if parent_object is set
    TransformData global_transform_;

    glm::vec3 look_at_;
    glm::vec3 direction;

    glm::mat4 ModelMatrix;
    glm::mat4 TranslateMatrix;
    glm::mat4 RotationMatrix;

    // If set, it defines the local coordinate system for this object
    Transformable* parent_object_;
};
}

#endif // PROJECT_TRANSFORM_H
