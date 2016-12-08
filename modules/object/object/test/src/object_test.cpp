#include "gtest/gtest.h"

#include <object/movable_object.h>

TEST(basic_check, test_eq) {
    ifx::MovableObject object(ObjectID(0));

    EXPECT_EQ(1, 0);
}