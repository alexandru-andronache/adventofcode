#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day04 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2016/day04/input_test.in"), 1514);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day04/input.in"), 137896);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day04/input.in"), 501);
    }
}