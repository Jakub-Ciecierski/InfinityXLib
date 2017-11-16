#ifndef PROJECT_MESH_COLLISION_SHAPE_H
#define PROJECT_MESH_COLLISION_SHAPE_H

#include <physics/collision/collision_shape.h>

namespace ifx {

class MeshCollisionShape : public CollisionShape{
public:

    MeshCollisionShape();

    ~MeshCollisionShape() = default;

    virtual void InitImpl(RigidBodyImpl *rigid_body_impl) override;
private:
};
}


#endif //PROJECT_MESH_COLLISION_SHAPE_H
