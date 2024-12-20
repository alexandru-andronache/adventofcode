#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day03 {
    TEST_F(Tests2024Day03, part_1_test) {
        ASSERT_EQ(part_1("../2024/day03/input_test.in"), 161);
    }

    TEST_F(Tests2024Day03, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day03/input.in"), 182619815);
    }

    TEST_F(Tests2024Day03, part_2_test) {
        ASSERT_EQ(part_2("../2024/day03/input_test2.in"), 48);
    }

    TEST_F(Tests2024Day03, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day03/input.in"), 80747545);
    }
}