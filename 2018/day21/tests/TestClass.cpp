#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day21 {
    TEST_F(Tests2018Day21, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day21/input.in"), 10147168);
    }

    TEST_F(Tests2018Day21, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day21/input.in"), 15929730);
    }
}