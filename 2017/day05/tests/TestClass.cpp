#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day05 {
    TEST_F(Tests2017Day05, part_1_test) {
        ASSERT_EQ(part_1("../2017/day05/input_test.in"), 5);
    }

    TEST_F(Tests2017Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day05/input.in"), 372139);
    }

    TEST_F(Tests2017Day05, part_2_test) {
        ASSERT_EQ(part_2("../2017/day05/input_test.in"), 10);
    }

    TEST_F(Tests2017Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day05/input.in"), 29629538);
    }
}