#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day01 {
    TEST_F(Tests2015Day01, part_1_test) {
        ASSERT_EQ(part_1("../2015/day01/input_test.in"), -1);
    }

    TEST_F(Tests2015Day01, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day01/input.in"), 74);
    }

    TEST_F(Tests2015Day01, part_2_test) {
        ASSERT_EQ(part_2("../2015/day01/input_test.in"), 5);
    }

    TEST_F(Tests2015Day01, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day01/input.in"), 1795);
    }
}