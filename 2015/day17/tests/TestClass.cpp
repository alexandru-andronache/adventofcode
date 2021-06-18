#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day17{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day17/input_test.in", 25), 4);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day17/input.in", 150), 654);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day17/input_test.in", 25), 3);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day17/input.in", 150), 57);
    }
}