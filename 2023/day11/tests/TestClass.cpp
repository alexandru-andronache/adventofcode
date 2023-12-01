#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day11 {
    TEST_F(Tests2023Day11, part_1_test) {
        ASSERT_EQ(part_1("../2023/day11/input_test.in"), 0);
    }

    TEST_F(Tests2023Day11, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day11/input.in"), 0);
    }

    TEST_F(Tests2023Day11, part_2_test) {
        ASSERT_EQ(part_2("../2023/day11/input_test.in"), 0);
    }

    TEST_F(Tests2023Day11, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day11/input.in"), 0);
    }
}