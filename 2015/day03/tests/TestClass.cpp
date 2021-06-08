#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day03 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day03/input_test.in"), 2);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day03/input.in"), 2081);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day03/input_test.in"), 11);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day03/input.in"), 2341);
    }
}