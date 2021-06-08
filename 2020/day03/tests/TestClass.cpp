#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day03 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day03/input_test.in"), 7);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day03/input.in"), 191);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day03/input_test.in"), 336);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day03/input.in"), 1478615040);
    }
}