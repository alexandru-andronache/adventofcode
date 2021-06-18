#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day03 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day03/input.in"), 869);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day03/input.in"), 1544);
    }
}