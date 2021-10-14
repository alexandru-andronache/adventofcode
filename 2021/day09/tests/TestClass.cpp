#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day09 {
    TEST_F(Tests2021Day09, part_1_test) {
        ASSERT_EQ(part_1("../2021/day09/input_test.in"), 0);
    }

    TEST_F(Tests2021Day09, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day09/input.in"), 0);
    }

    TEST_F(Tests2021Day09, part_2_test) {
        ASSERT_EQ(part_2("../2021/day09/input_test.in"), 0);
    }

    TEST_F(Tests2021Day09, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day09/input.in"), 0);
    }
}
