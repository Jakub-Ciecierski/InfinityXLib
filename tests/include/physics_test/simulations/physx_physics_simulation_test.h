#include "gtest/gtest.h"

#include <memory>

namespace ifx{
class PhysxPhysicsSimulation;
}

class PhysxPhysicsSimulationTest : public ::testing::Test {
protected:
    virtual void SetUp() override;

    virtual void TearDown() override;

    std::shared_ptr<ifx::PhysxPhysicsSimulation> simulation_;
};
