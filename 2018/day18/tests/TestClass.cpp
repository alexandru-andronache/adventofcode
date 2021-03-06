#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day18 {
    TEST_F(Tests2018Day18, part_1_test) {
        ASSERT_EQ(part_1("../2018/day18/input_test.in"), 1147);
    }

    TEST_F(Tests2018Day18, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day18/input.in"), 574590);
    }

    TEST_F(Tests2018Day18, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day18/input.in"), 183787);
    }
}