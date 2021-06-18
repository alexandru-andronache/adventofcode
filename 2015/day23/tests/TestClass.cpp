#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day23 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day23/input_test.in", 0), 2);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day23/input.in", 1), 170);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day23/input.in", 1), 247);
    }
}
