#ifndef PROJECT_MOVABLE_OBJECT_H
#define PROJECT_MOVABLE_OBJECT_H

#include <math/math_ifx.h>
#include <object/object.h>

namespace ifx {

class MovableObject : public Object {
public:

    MovableObject();
    MovableObject(ObjectID id);

    ~MovableObject();

    const glm::vec3& look_at(){return look_at_;}

    // Overridden from Object
    virtual void update() override;

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

protected:
    void initVectors();

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaleFactor;

    glm::vec3 look_at_;
    glm::vec3 direction;

    glm::mat4 ModelMatrix;
    glm::mat4 TranslateMatrix;
    glm::mat4 RotationMatrix;

private:

};
}

#endif //PROJECT_MOVABLE_OBJECT_H
