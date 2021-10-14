#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day01 {
    TEST_F(Tests2016Day01, part_1_test) {
        ASSERT_EQ(part_1("../2016/day01/input_test.in"), 12);
    }

    TEST_F(Tests2016Day01, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day01/input.in"), 301);
    }

    TEST_F(Tests2016Day01, part_2_test) {
        ASSERT_EQ(part_2("../2016/day01/input_test2.in"), 4);
    }

    TEST_F(Tests2016Day01, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day01/input.in"), 130);
    }
}