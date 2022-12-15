#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day15 {
    TEST_F(Tests2022Day15, part_1_test) {
        ASSERT_EQ(part_1("../2022/day15/input_test.in", 10), 26);
    }

    TEST_F(Tests2022Day15, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day15/input.in", 2000000), 6425133);
    }

    TEST_F(Tests2022Day15, part_2_test) {
        ASSERT_EQ(part_2("../2022/day15/input_test.in", 20), 56000011);
    }

    TEST_F(Tests2022Day15, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day15/input.in", 4000000), 10996191429555);
    }
}