#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day05 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day05/input_test.in"), 0);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day05/input.in"), 0);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day05/input_test.in"), 0);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day05/input.in"), 0);
    }
}