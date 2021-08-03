#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day05 {
    TEST_F(Tests2018Day05, part_1_test) {
        ASSERT_EQ(part_1("../2018/day05/input_test.in"), 10);
    }

    TEST_F(Tests2018Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day05/input.in"), 9060);
    }

    TEST_F(Tests2018Day05, part_2_test) {
        ASSERT_EQ(part_2("../2018/day05/input_test.in"), 4);
    }

    TEST_F(Tests2018Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day05/input.in"), 6310);
    }
}