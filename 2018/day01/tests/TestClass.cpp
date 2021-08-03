#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day01 {
    TEST_F(Tests2018Day01, part_1_test) {
        ASSERT_EQ(part_1("../2018/day01/input_test.in"), 4);
    }

    TEST_F(Tests2018Day01, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day01/input.in"), 484);
    }

    TEST_F(Tests2018Day01, part_2_test) {
        ASSERT_EQ(part_2("../2018/day01/input_test.in"), 10);
    }

    TEST_F(Tests2018Day01, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day01/input.in"), 367);
    }
}