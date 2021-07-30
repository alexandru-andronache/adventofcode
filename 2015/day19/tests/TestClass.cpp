#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day19 {
    TEST_F(Tests2015Day19, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day19/input.in"), 509);
    }

    TEST_F(Tests2015Day19, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day19/input.in"), 195);
    }
}