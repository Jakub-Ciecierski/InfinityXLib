#ifndef PROJECT_PHYSICSSIMULATIONFACTORY_H
#define PROJECT_PHYSICSSIMULATIONFACTORY_H

#include <memory>

class btDiscreteDynamicsWorld;

namespace ifx {

struct BulletPhysicsSimulationCreateParams;
class PhysicsSimulation;

enum class DynamicWorldType {
    DISCRETE, FRACTURE
};

class BulletPhysicsSimulationFactory {
public:

    BulletPhysicsSimulationFactory();
    ~BulletPhysicsSimulationFactory();

    virtual std::shared_ptr<PhysicsSimulation> Create();

    BulletPhysicsSimulationFactory& SetDynamicWorldType(DynamicWorldType type);

private:
    std::shared_ptr<BulletPhysicsSimulationCreateParams>
            CreateBulletDynamics();

    std::shared_ptr<btDiscreteDynamicsWorld> CreateDiscreteDynamicWorld(
            const std::shared_ptr<BulletPhysicsSimulationCreateParams>);

    DynamicWorldType dynamic_world_type_;
};
}

#endif //PROJECT_PHYSICSSIMULATIONFACTORY_H
