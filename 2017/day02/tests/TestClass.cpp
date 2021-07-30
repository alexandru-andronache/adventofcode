#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day02 {
    TEST_F(Tests2017Day02, part_1_test) {
        ASSERT_EQ(part_1("../2017/day02/input_test.in"), 18);
    }

    TEST_F(Tests2017Day02, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day02/input.in"), 47136);
    }

    TEST_F(Tests2017Day02, part_2_test) {
        ASSERT_EQ(part_2("../2017/day02/input_test2.in"), 9);
    }

    TEST_F(Tests2017Day02, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day02/input.in"), 250);
    }
}