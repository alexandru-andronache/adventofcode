#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day15 {
    TEST_F(Tests2021Day15, part_1_test) {
        ASSERT_EQ(part_1("../2021/day15/input_test.in"), 40);
    }

    TEST_F(Tests2021Day15, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day15/input.in"), 824);
    }

    TEST_F(Tests2021Day15, part_2_test) {
        ASSERT_EQ(part_2("../2021/day15/input_test.in"), 315);
    }

    TEST_F(Tests2021Day15, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day15/input.in"), 3063);
    }
}