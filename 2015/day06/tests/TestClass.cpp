#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day06 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day06/input_test.in"), 998996);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day06/input.in"), 543903);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day06/input_test.in"), 1001996);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day06/input.in"), 14687245);
    }
}