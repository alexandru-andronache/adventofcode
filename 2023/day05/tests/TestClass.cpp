#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day05 {
    TEST_F(Tests2023Day05, part_1_test) {
        ASSERT_EQ(part_1("../2023/day05/input_test.in"), 35);
    }

    TEST_F(Tests2023Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day05/input.in"), 157211394);
    }

    TEST_F(Tests2023Day05, part_2_test) {
        ASSERT_EQ(part_2("../2023/day05/input_test.in"), 46);
    }

    TEST_F(Tests2023Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day05/input.in"), 0);
    }
}