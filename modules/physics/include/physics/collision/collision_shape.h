#ifndef PROJECT_COLLISION_SHAPE_H
#define PROJECT_COLLISION_SHAPE_H

#include <memory>
#include <math/math_ifx.h>

class btCollisionShape;

namespace ifx {

class RigidBodyImpl;

enum class CollisionShapeType{
    StaticPlane, Box, Sphere
};

inline std::string CollisionShapeName(CollisionShapeType type){
    switch (type){
        case CollisionShapeType::Box:
            return "Box Collider";
        case CollisionShapeType::Sphere:
            return "Sphere Collider";
        case CollisionShapeType::StaticPlane:
            return "Static Plane Collider";
        default:
            return "Unknown";
    }
}

class CollisionShape {
public:

    CollisionShape(CollisionShapeType type);
    virtual ~CollisionShape() = default;

    const glm::vec3 &scale() { return scale_; }
    void scale(const glm::vec3 &scale) { scale_ = scale; }

    CollisionShapeType type(){return type_;}

    virtual void InitImpl(RigidBodyImpl *rigid_body_impl) = 0;
private:
    glm::vec3 scale_;

    CollisionShapeType type_;
};

}

#endif //PROJECT_COLLISION_SHAPE_H
