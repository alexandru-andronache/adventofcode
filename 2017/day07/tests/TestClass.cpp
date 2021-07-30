#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day07 {
    TEST_F(Tests2017Day07, part_1_test) {
        ASSERT_EQ(part_1("../2017/day07/input_test.in"), "tknk");
    }

    TEST_F(Tests2017Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day07/input.in"), "hlqnsbe");
    }

    TEST_F(Tests2017Day07, part_2_test) {
        ASSERT_EQ(part_2("../2017/day07/input_test.in"), 60);
    }

    TEST_F(Tests2017Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day07/input.in"), 1993);
    }
}