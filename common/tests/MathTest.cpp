#include "MathTest.h"
#include "math_util.h"

using namespace math;

TEST_F(MathTest, modular_inverse) {
    ASSERT_EQ(modularInverse(75, 119315717514047), 106588707645882);
    ASSERT_EQ(modularInverse(33, 119315717514047), 3615627803456);
}

TEST_F(MathTest, power_test) {
    ASSERT_EQ(modular_power(41443368465112, 101741582076661, 119315717514047), 96656040088959);
    ASSERT_EQ(modular_power(2, 10, 1000), 24);
}

TEST_F(MathTest, mod_test) {
    ASSERT_EQ(mod(-7249, 10007), 2758);
    ASSERT_EQ(mod(305760, 10007), 5550);
}

TEST_F(MathTest, modular_divide_test) {
    ASSERT_EQ(modular_divide(96656040088958, 41443368465111, 119315717514047), 98841558257567);
}