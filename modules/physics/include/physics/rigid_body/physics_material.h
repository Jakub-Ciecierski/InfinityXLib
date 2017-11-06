#ifndef PROJECT_PHYSICS_MATERIAL_H
#define PROJECT_PHYSICS_MATERIAL_H

namespace ifx {

struct PhysicsMaterial {
public:
    PhysicsMaterial() :
            dynamic_friction(0.5),
            static_friction(0.5),
            restitution(0.1){}

    PhysicsMaterial(float dynamic_friction_,
                    float static_friction_,
                    float restitution_) :
            dynamic_friction(dynamic_friction_),
            static_friction(static_friction_),
            restitution(restitution_) {}

    ~PhysicsMaterial() = default;

    float dynamic_friction;
    float static_friction;
    float restitution;

private:
};
}


#endif //PROJECT_PHYSICS_MATERIAL_H
