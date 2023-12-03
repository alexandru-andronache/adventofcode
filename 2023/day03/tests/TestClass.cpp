#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day03 {
    TEST_F(Tests2023Day03, part_1_test) {
        ASSERT_EQ(part_1("../2023/day03/input_test.in"), 4361);
    }

    TEST_F(Tests2023Day03, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day03/input.in"), 556057);
    }

    TEST_F(Tests2023Day03, part_2_test) {
        ASSERT_EQ(part_2("../2023/day03/input_test.in"), 467835);
    }

    TEST_F(Tests2023Day03, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day03/input.in"), 82824352);
    }
}