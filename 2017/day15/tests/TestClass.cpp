#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day15 {
    TEST_F(Tests2017Day15, part_1_test) {
        ASSERT_EQ(part_1(65, 8921), 588);
    }

    TEST_F(Tests2017Day15, part_1_real_test) {
        ASSERT_EQ(part_1(722, 354), 612);
    }

    TEST_F(Tests2017Day15, part_2_test) {
        ASSERT_EQ(part_2(65, 8921), 309);
    }

    TEST_F(Tests2017Day15, part_2_real_test) {
        ASSERT_EQ(part_2(722, 354), 285);
    }
}