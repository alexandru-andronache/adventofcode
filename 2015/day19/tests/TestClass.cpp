#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day19 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day19/input.in"), 509);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day19/input.in"), 195);
    }
}