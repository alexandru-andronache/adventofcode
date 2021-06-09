#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day02 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day02/input_test.in"), 101);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day02/input.in"), 1598415);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day02/input_test.in"), 48);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day02/input.in"), 3812909);
    }
}