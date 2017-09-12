#include "gtest/gtest.h"

#include <RTFEM/FEM/Meshing/Tetrahedralization.h>

class RTFEMTests : public testing::Test {
protected:

    virtual void SetUp() {

    }

};

TEST_F(RTFEMTests, Intergration) {
    rtfem::Tetrahedralization<float> tetrahedralization;
}
