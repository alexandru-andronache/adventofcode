#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day15 {
    TEST_F(Tests2018Day15, part_1_test) {
        ASSERT_EQ(part_1("../2018/day15/input_test.in"), 36334);
    }

    TEST_F(Tests2018Day15, part_1_test_2) {
        ASSERT_EQ(part_1("../2018/day15/input_test2.in"), 28944);
    }

    TEST_F(Tests2018Day15, part_1_test_3) {
        ASSERT_EQ(part_1("../2018/day15/input_test3.in"), 18740);
    }

    TEST_F(Tests2018Day15, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day15/input.in"), 207059);
    }

    TEST_F(Tests2018Day15, part_2_test) {
        ASSERT_EQ(part_2("../2018/day15/input_test2.in"), 6474);
    }

    TEST_F(Tests2018Day15, part_2_test_2) {
        ASSERT_EQ(part_2("../2018/day15/input_test3.in"), 1140);
    }

    TEST_F(Tests2018Day15, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day15/input.in"), 49120);
    }
}