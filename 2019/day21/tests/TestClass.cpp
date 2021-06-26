#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day21 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day21/input.in"), 19359316);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day21/input.in"), 1141281622);
    }
}