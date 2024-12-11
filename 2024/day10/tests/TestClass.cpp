#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day10{
    TEST_F(Tests2024Day10, part_1_test) {
        ASSERT_EQ(part_1("../2024/day10/input_test.in"), 36);
    }

    TEST_F(Tests2024Day10, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day10/input.in"), 717);
    }

    TEST_F(Tests2024Day10, part_2_test) {
        ASSERT_EQ(part_2("../2024/day10/input_test.in"), 81);
    }

    TEST_F(Tests2024Day10, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day10/input.in"), 1686);
    }
}