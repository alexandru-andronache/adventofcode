#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day10{
    TEST_F(Tests2021Day10, part_1_test) {
        ASSERT_EQ(part_1("../2021/day10/input_test.in"), 26397);
    }

    TEST_F(Tests2021Day10, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day10/input.in"), 266301);
    }

    TEST_F(Tests2021Day10, part_2_test) {
        ASSERT_EQ(part_2("../2021/day10/input_test.in"), 288957);
    }

    TEST_F(Tests2021Day10, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day10/input.in"), 3404870164);
    }
}