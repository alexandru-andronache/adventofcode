#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day21 {
    TEST_F(Tests2024Day21, part_1_test) {
        ASSERT_EQ(part_1("../2024/day21/input_test.in"), 0);
    }

    TEST_F(Tests2024Day21, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day21/input.in"), 0);
    }

    TEST_F(Tests2024Day21, part_2_test) {
        ASSERT_EQ(part_2("../2024/day21/input_test.in"), 0);
    }

    TEST_F(Tests2024Day21, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day21/input.in"), 0);
    }
}