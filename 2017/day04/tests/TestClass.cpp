#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day04 {
    TEST_F(Tests2017Day04, part_1_test) {
        ASSERT_EQ(part_1("../2017/day04/input_test.in"), 2);
    }

    TEST_F(Tests2017Day04, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day04/input.in"), 466);
    }

    TEST_F(Tests2017Day04, part_2_test) {
        ASSERT_EQ(part_2("../2017/day04/input_test2.in"), 3);
    }

    TEST_F(Tests2017Day04, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day04/input.in"), 251);
    }
}