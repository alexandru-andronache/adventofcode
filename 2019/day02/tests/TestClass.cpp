#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day02 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day02/input.in"), 3716250);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day02/input.in"), 6472);
    }
}