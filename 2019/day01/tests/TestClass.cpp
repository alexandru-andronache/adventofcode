#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day01 {
    TEST_F(Tests2019Day01, part_1_test) {
        ASSERT_EQ(part_1("../2019/day01/input_test.in"), 34241);
    }

    TEST_F(Tests2019Day01, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day01/input.in"), 3252897);
    }

    TEST_F(Tests2019Day01, part_2_test) {
        ASSERT_EQ(part_2("../2019/day01/input_test.in"), 51316);
    }

    TEST_F(Tests2019Day01, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day01/input.in"), 4876469);
    }
}