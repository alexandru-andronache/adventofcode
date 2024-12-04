#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day04 {
    TEST_F(Tests2024Day04, part_1_test) {
        ASSERT_EQ(part_1("../2024/day04/input_test.in"), 18);
    }

    TEST_F(Tests2024Day04, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day04/input.in"), 2593);
    }

    TEST_F(Tests2024Day04, part_2_test) {
        ASSERT_EQ(part_2("../2024/day04/input_test.in"), 9);
    }

    TEST_F(Tests2024Day04, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day04/input.in"), 1950);
    }
}