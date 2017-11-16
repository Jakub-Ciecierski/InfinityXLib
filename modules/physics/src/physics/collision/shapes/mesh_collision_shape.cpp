#include "physics/collision/shapes/mesh_collision_shape.h"

#include <physics/rigid_body/impl/rigid_body_impl.h>

namespace ifx {

MeshCollisionShape::MeshCollisionShape() :
        CollisionShape(CollisionShapeType::Mesh){}

void MeshCollisionShape::InitImpl(RigidBodyImpl *rigid_body_impl){
    rigid_body_impl->InitCollisionShape(this);
}
}