#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day06 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day06/input_test.in"), 11);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day06/input.in"), 6551);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day06/input_test.in"), 6);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day06/input.in"), 3358);
    }
}