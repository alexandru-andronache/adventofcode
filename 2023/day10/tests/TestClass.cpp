#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day10{
    TEST_F(Tests2023Day10, part_1_test) {
        ASSERT_EQ(part_1("../2023/day10/input_test.in"), 8);
    }

    TEST_F(Tests2023Day10, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day10/input.in"), 6690);
    }

    TEST_F(Tests2023Day10, part_2_test) {
        ASSERT_EQ(part_2("../2023/day10/input_test2.in"), 4);
    }

    TEST_F(Tests2023Day10, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day10/input.in"), 525);
    }
}