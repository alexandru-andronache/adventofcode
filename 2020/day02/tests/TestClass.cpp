#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day02 {
    TEST_F(Tests2020Day02, part_1_test) {
        ASSERT_EQ(part_1("../2020/day02/input_test.in"), 2);
    }

    TEST_F(Tests2020Day02, part_1_real) {
        ASSERT_EQ(part_1("../2020/day02/input.in"), 524);
    }

    TEST_F(Tests2020Day02, part_2_test) {
        ASSERT_EQ(part_2("../2020/day02/input_test.in"), 1);
    }

    TEST_F(Tests2020Day02, part_2_real) {
        ASSERT_EQ(part_2("../2020/day02/input.in"), 485);
    }
}