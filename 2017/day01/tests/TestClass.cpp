#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day01 {
    TEST_F(Tests2017Day01, part_1_test) {
        ASSERT_EQ(part_1("../2017/day01/input_test.in"), 9);
    }

    TEST_F(Tests2017Day01, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day01/input.in"), 1049);
    }

    TEST_F(Tests2017Day01, part_2_test) {
        ASSERT_EQ(part_2("../2017/day01/input_test2.in"), 4);
    }

    TEST_F(Tests2017Day01, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day01/input.in"), 1508);
    }
}