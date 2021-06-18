#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day18 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day18/input_test.in", 4), 4);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day18/input.in", 100), 1061);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day18/input_test.in", 5), 17);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day18/input.in", 100), 1006);
    }
}