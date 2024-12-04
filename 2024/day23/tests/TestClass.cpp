#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day23 {
    TEST_F(Tests2024Day23, part_1_test) {
        ASSERT_EQ(part_1("../2024/day23/input_test.in"), 0);
    }

    TEST_F(Tests2024Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day23/input.in"), 0);
    }

    TEST_F(Tests2024Day23, part_2_test) {
        ASSERT_EQ(part_2("../2024/day23/input_test.in"), 0);
    }

    TEST_F(Tests2024Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day23/input.in"), 0);
    }
}