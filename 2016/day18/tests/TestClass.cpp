#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day18 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2016/day18/input_test.in", 3), 6);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day18/input.in", 40), 1987);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2016/day18/input_test2.in", 10), 38);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day18/input.in", 400000), 19984714);
    }
}