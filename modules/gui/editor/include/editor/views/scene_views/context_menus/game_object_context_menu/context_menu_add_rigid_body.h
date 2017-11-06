#ifndef PROJECT_CONTEXT_MENU_ADD_RIGID_BODY_H
#define PROJECT_CONTEXT_MENU_ADD_RIGID_BODY_H

#include <memory>

#include <physics/collision/collision_shape.h>
#include <physics/rigid_body/physics_material.h>

namespace ifx {

class PhysicsSimulation;
class RigidBodyComponent;
class GameObject;

struct RigidBodyParams;

struct CollidersSelectables{
    unsigned int selected = 0;

    const std::string box_name = "Box";
    static constexpr unsigned int box_id = 0;

    const std::string sphere_name = "Sphere";
    static constexpr unsigned int sphere_id = 1;

    const std::string static_plane_name = "Static Plane";
    static constexpr unsigned int static_plane_id = 2;

    const std::vector<std::string> names{
            box_name,
            sphere_name,
            static_plane_name,
    };

    const int GetID(std::string name)  {
        for (unsigned int i = 0; i < names.size(); i++) {
            if (names[i] == name) {
                return i;
            }
        }
        return -1;
    }
};

struct BoxConstructionData{
    glm::vec3 box_dim = glm::vec3(1, 1, 1);
};

struct SphereConstructionData{
    float radius = 1.0f;
};

struct StaticPlaneConstructionData{
    glm::vec3 plane_normal = glm::vec3(0, 1, 0);
    float plane_constant = 0;
};

class ContextMenuAddRigidBody {
public:

    ContextMenuAddRigidBody(
            std::shared_ptr<PhysicsSimulation> physics_simulation);
    ~ContextMenuAddRigidBody() = default;

    void Render(std::shared_ptr<GameObject> game_object);
private:
    void RenderPopWindow(std::shared_ptr<GameObject> game_object);

    void RenderMass();
    void RenderPhysicsMaterial();

    void RenderCollisionType();
    void RenderCollisionData();
    void RenderBoxConstructionData();
    void RenderSphereConstructionData();
    void RenderStaticPlaneConstructionData();

    void RenderFooter(std::shared_ptr<GameObject> game_object);

    std::shared_ptr<RigidBodyComponent> Create();
    RigidBodyParams CreateRigidBodyParams();

    std::shared_ptr<PhysicsSimulation> physics_simulation_;

    CollidersSelectables colliders_selectables_;

    CollisionShapeType collision_shape_type_;
    float mass_;
    PhysicsMaterial physics_material_;

    BoxConstructionData box_construction_data_;
    SphereConstructionData sphere_construction_data_;
    StaticPlaneConstructionData static_plane_construction_data_;
};
}


#endif //PROJECT_CONTEXT_MENU_ADD_RIGID_BODY_H
