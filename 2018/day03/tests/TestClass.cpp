#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day03 {
    TEST_F(Tests2018Day03, part_1_test) {
        ASSERT_EQ(part_1("../2018/day03/input_test.in"), 0);
    }

    TEST_F(Tests2018Day03, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day03/input.in"), 0);
    }

    TEST_F(Tests2018Day03, part_2_test) {
        ASSERT_EQ(part_2("../2018/day03/input_test.in"), 0);
    }

    TEST_F(Tests2018Day03, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day03/input.in"), 0);
    }
}