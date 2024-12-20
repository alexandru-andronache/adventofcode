#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day01 {
    TEST_F(Tests2024Day01, part_1_test) {
        ASSERT_EQ(part_1("../2024/day01/input_test.in"), 11);
    }

    TEST_F(Tests2024Day01, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day01/input.in"), 1151792);
    }

    TEST_F(Tests2024Day01, part_2_test) {
        ASSERT_EQ(part_2("../2024/day01/input_test.in"), 31);
    }

    TEST_F(Tests2024Day01, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day01/input.in"), 21790168);
    }
}