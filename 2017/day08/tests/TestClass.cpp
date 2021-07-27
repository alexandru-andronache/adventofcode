#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day08{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2017/day08/input_test.in"), 1);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day08/input.in"), 5966);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2017/day08/input_test.in"), 10);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day08/input.in"), 6347);
    }
}