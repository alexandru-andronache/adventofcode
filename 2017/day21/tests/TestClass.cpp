#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day21 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day21/input.in"), 133);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day21/input.in"), 2221990);
    }
}