#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day11 {
    TEST_F(Tests2024Day11, part_1_small_test) {
        ASSERT_EQ(part_1("../2024/day11/input_test.in", 6), 22);
    }

    TEST_F(Tests2024Day11, part_1_test) {
        ASSERT_EQ(part_1("../2024/day11/input_test.in", 25), 55312);
    }

    TEST_F(Tests2024Day11, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day11/input.in"), 220999);
    }

    TEST_F(Tests2024Day11, part_2_test) {
        ASSERT_EQ(part_2("../2024/day11/input_test.in"), 65601038650482);
    }

    TEST_F(Tests2024Day11, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day11/input.in"), 261936432123724);
    }
}