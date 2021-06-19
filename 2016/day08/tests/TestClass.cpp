#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day08{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2016/day08/input_test.in"), 6);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day08/input.in"), 123);
    }
}