#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day05 {
    TEST_F(Tests2021Day05, part_1_test) {
        ASSERT_EQ(part_1("../2021/day05/input_test.in"), 5);
    }

    TEST_F(Tests2021Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day05/input.in"), 6666);
    }

    TEST_F(Tests2021Day05, part_2_test) {
        ASSERT_EQ(part_2("../2021/day05/input_test.in"), 12);
    }

    TEST_F(Tests2021Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day05/input.in"), 19081);
    }
}